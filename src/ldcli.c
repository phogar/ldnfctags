/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
 * Copyright (C) 2016  <>
 *
 * ldnfccli is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ldnfccli is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <glib.h>
#include <string.h>
#include "legodimensions.h"
#include "legodimensions_characters.h"
#include "legodimensions_vehicles.h"
#include "ldnfc.h"

/* Define Option Parser Callback functions */
gboolean
post_parse_option_group_command_func(GOptionContext *context, GOptionGroup *group, gpointer data, GError **error);

/*  structure to store command line options: */
typedef struct {
    gboolean command_list;
    gboolean command_read;
    gboolean command_initialize;
    gint     character_id;
    gint     vehicle_id;
    gboolean (*command_func)(GError **);
    gboolean write;
    gboolean blocking;
} cli_args_t;

static cli_args_t cli_args = { FALSE, FALSE, FALSE, -1, -1, NULL, FALSE, FALSE};

// Method declaration for command callbacks
gboolean ldcli_list_ntags(GError **error_);
gboolean ldcli_read_tag(GError **error_);
gboolean ldcli_write_character(GError **error_);
gboolean ldcli_write_vehicle(GError **error_);



static GOptionEntry optentries_main[] =
{
    { "blocking", 'b', 0, G_OPTION_ARG_NONE, &cli_args.blocking,
        "Wait infinite for NFC tag."},
    { "write",   'w', 0, G_OPTION_ARG_NONE, &cli_args.write,
        "Per default writing to a NFC tag is disable. Use this flag to enable writing."},

    { NULL }
};

static GOptionEntry optentries_commands[] =
{
    /* list of mutually exclusive commands */
    { "list",      'l', 0, G_OPTION_ARG_NONE, &cli_args.command_list,
        "List known characters."},
    { "read",      'r', 0, G_OPTION_ARG_NONE, &cli_args.command_read,
        "Read NFC tag and dump information."},
    { "character",     'c', 0, G_OPTION_ARG_INT, &cli_args.character_id,
        "Write character with id CID to NFC tag. [" G_STRINGIFY(LD_MIN_CID) "<CID<" G_STRINGIFY(LD_MAX_CID) "]", "CID"},
    { "initialize",    'i', 0, G_OPTION_ARG_NONE, &cli_args.command_initialize,
        "Initialize NFC tag for character usage. Lego Dimensions pad will accept the tag as an empty vehicle/gadget tag."},
    { "vehicle", 'v', 0,  G_OPTION_ARG_INT, &cli_args.vehicle_id,
        "Write vehicle with id VID to NFC tag. [0<=VID<1000]", "VID"},
    {NULL}
};


   /** \brief Callback method for glib option parser. Check if user has selected one command.
    *         Only one operation at a time is allowed. Sets the commands function pointer to cli_args structrure.
    */
gboolean
post_parse_option_group_command_func(GOptionContext *context, GOptionGroup *group, gpointer data, GError **error){
    cli_args_t *cli_args = (cli_args_t*) data;
    g_assert(cli_args);
    gboolean result = TRUE;

    if (!(
            (cli_args->command_list     )
          ^ (cli_args->command_read     )
          ^ (cli_args->command_initialize)
          ^ (cli_args->character_id > -1)
          ^ (cli_args->vehicle_id   > -1)
        )
    ){
            g_set_error( error, G_OPTION_ERROR, UL_ERROR
                , "Please define one command of 'list', 'read', 'character', 'initialice' and 'vehicle'.");
        result = FALSE;
    } else

    if ( cli_args->command_list == TRUE ){
        ((cli_args_t*) data)->command_func = &ldcli_list_ntags;
    } else
    if ( cli_args->command_read == TRUE ){
        ((cli_args_t*) data)->command_func = &ldcli_read_tag;
    } else
    if ( cli_args->character_id > -1 ){
        if(!LD_CID_VALID(cli_args->character_id)){
            g_set_error(error, G_OPTION_ERROR, UL_ERROR,
                        "Character ID(%d) is out of range("
                        G_STRINGIFY(LD_MIN_CID)".."G_STRINGIFY(LD_MAX_CID)").", cli_args->character_id);
            result = FALSE;
        } else {
            ((cli_args_t*) data)->command_func = &ldcli_write_character;
        }
    } else
    if( cli_args->vehicle_id   > -1 ){
        if(cli_args->vehicle_id > 999){
            g_set_error(error, G_OPTION_ERROR, UL_ERROR, "Vehicle ID(%d) is out of range(0..999).", cli_args->vehicle_id);
            result = FALSE;
        } else {
            ((cli_args_t*) data)->command_func = &ldcli_write_vehicle;
        }
    } else
    if ( cli_args->command_initialize){
        ((cli_args_t*) data)->command_func = &ldcli_write_vehicle;

    }
    return result;
} /* post_parse_option_command_func */


gboolean
ldcli_list_ntags(GError **error_){
    g_print("List of known characters:\n");
    ld_print_characters();
    g_print("List of known vehicles:\n");
    ld_print_vehicles();
    return TRUE;
} /* ldcli_list_ntags */


gboolean
ldcli_read_tag(GError **error_){
    app_ctx   ul_context;
    ul_result nfc_result;
    gboolean  result = FALSE;
    guint32   pages_0x24[4];
    guint     ntag_id;

    if( error_ ) g_assert_null (*error_);

    if( FALSE == ldnfc_open_tag(&ul_context, error_)) goto lbl_read_finalize;

    // Get pages for NTAG ID
    if (FALSE == ldnfc_read_two_pages(&ul_context, 0x24, pages_0x24+0, pages_0x24+1, error_)) goto lbl_read_finalize;
    // Get page to distinguish between character and vehicle
    if (FALSE == ldnfc_read_two_pages(&ul_context, 0x26, pages_0x24+2, pages_0x24+3, error_)) goto lbl_read_finalize;

    if( !pages_0x24[0] && !pages_0x24[1] && !pages_0x24[2] ){
        g_print(" - Empty Tag detected\n");
    } else
    if ( pages_0x24[2] == 0x00010000){
        g_print( " - Vehicle detected " );
        ntag_id = ld_decode_vehicle_id(pages_0x24);
        ld_print_vehicle_by_id(ntag_id);
    } else {

        g_print( " - Character detected ");
        ntag_id = ld_decrypt_character_pages(ul_context.uldev.id, pages_0x24);
        ld_print_character_by_id(ntag_id);
    }

    result = TRUE;
lbl_read_finalize:
    nfc_close(ul_context.nfcdev);
    nfc_exit(ul_context.nfcctx);

    return result;
} /* ldcli_read_tag */


gboolean
ldcli_write_vehicle(GError **error_){
    app_ctx  ul_context;
    gboolean result = FALSE;
    ul_result nfc_result;
    guint32 ld_pwd;
    guint32 vehicle_page = GUINT32_TO_BE(cli_args.vehicle_id +1000);
    guint32 buf[2];



    if( FALSE == cli_args.command_initialize ){
        const ntag_t *vehicle = ld_get_vehicle_by_id(cli_args.vehicle_id, error_);
        if( !vehicle ) return FALSE;
        g_print("Selected vehicle: %s: %s\n", vehicle->name, vehicle->world);
    }


    if (FALSE == ldnfc_open_tag(&ul_context, error_)) return FALSE;


    g_info("Calculating PWD page[0x2b]\n");
    ld_pwd = ld_genpwd(ul_context.uldev.id);
    g_print(" - PWD: [0x2b]%08x\n", ld_pwd);


    ul_context.uldev.hasKey = false;
    if (FALSE == cli_args.write) {
        g_print("Writing is disable by default. Skipping.\n");
        result = TRUE;
        goto lbl_finalize;
    }


    // Write encrypted TAGID, password
    if (nfc_result = ul_writepage(&ul_context.uldev, 0x2b, ld_pwd)){
       g_set_error_literal(error_, LD_NFC_ERROR, nfc_result, "Failed to write to NFC tag");
       goto lbl_finalize;
    }

   // Verify before write: Check if tag is already marked as vehicle:
    if ( FALSE== ldnfc_read_two_pages(&ul_context, 0x26, buf, buf+1, error_ )) goto lbl_finalize;
    if ( buf[0] != 0x00010000 ) {
        // Set vehicle/gadget flag
        if( nfc_result = ul_writepage(&ul_context.uldev, 0x26, 0x00010000)){
            g_set_error_literal(error_, LD_NFC_ERROR, nfc_result, "Failed to write to NFC tag");
            goto lbl_finalize;
        }
    }


    if( TRUE == cli_args.command_initialize ){
        // Clear second page of encrypted character id
        if( nfc_result = ul_writepage(&ul_context.uldev, 0x24, 0)){
            g_set_error_literal(error_, LD_NFC_ERROR, nfc_result, "Failed to write to NFC tag");
            goto lbl_finalize;
        }

        // Clear second page of encrypted character id
        if( nfc_result = ul_writepage(&ul_context.uldev, 0x25, 0)){
            g_set_error_literal(error_, LD_NFC_ERROR, nfc_result, "Failed to write to NFC tag");
            goto lbl_finalize;
        }
        result = TRUE;
        goto lbl_finalize;
    }

    // Write first page of encrypted character id
    if( nfc_result = ul_writepage(&ul_context.uldev, 0x24, vehicle_page)){
        g_set_error_literal(error_, LD_NFC_ERROR, nfc_result, "Failed to write to NFC tag");
        goto lbl_finalize;
    }

    // Clear second page of encrypted character id
    if( nfc_result = ul_writepage(&ul_context.uldev, 0x25, 0)){
        g_set_error_literal(error_, LD_NFC_ERROR, nfc_result, "Failed to write to NFC tag");
        goto lbl_finalize;
    }


    g_print("Finished. Tag was written successfully.\n");
    result = TRUE;
lbl_finalize:
    nfc_close(ul_context.nfcdev);
    nfc_exit(ul_context.nfcctx);
    return result;
} /* ldcli_write_vehicle */


gboolean
ldcli_write_character(GError **error_){
    app_ctx  ul_context;
    gboolean result = FALSE;
    ul_result nfc_result;
    guint32 ld_pwd;
    guint32 chr_crypt[2];

    g_print("Selected character: ");
    ld_print_character_by_id(cli_args.character_id);


    if (FALSE == ldnfc_open_tag(&ul_context, error_)){
        return FALSE;
    }

    g_info("Calculating character pages[0x24:0x25]\n");
    ld_encrypt(ul_context.uldev.id, cli_args.character_id, chr_crypt);
    g_print(" - CHARID(%u): [0x24]%08x [0x25]%08x\n",
        cli_args.character_id,
        chr_crypt[0],
        chr_crypt[1]
    );

    g_info("Calculating PWD page[0x2b]\n");
    ld_pwd = ld_genpwd(ul_context.uldev.id);
    g_print(" - PWD: [0x2b]%08x\n", ld_pwd);

    if (FALSE == cli_args.write) {
        g_print("Writing is disable by default. Skipping.\n");
        result = TRUE;
        goto lbl_finalize;
    }

    // Write encrypted TAGID, password
    if (nfc_result = ul_writepage(&ul_context.uldev, 0x2b, ld_pwd)){
       g_set_error_literal(error_, LD_NFC_ERROR, nfc_result, "Failed to write to NFC tag");
       goto lbl_finalize;
    }

    // Write first page of encrypted character id
    if( nfc_result = ul_writepage(&ul_context.uldev, 0x24, chr_crypt[0])){
        g_set_error_literal(error_, LD_NFC_ERROR, nfc_result, "Failed to write to NFC tag");
        goto lbl_finalize;
    }

    // Write second page of encrypted character id
    if( nfc_result = ul_writepage(&ul_context.uldev, 0x25, chr_crypt[1])){
        g_set_error_literal(error_, LD_NFC_ERROR, nfc_result, "Failed to write to NFC tag");
        goto lbl_finalize;
    }

    // Clear vehicle/gadget page
    if( nfc_result = ul_writepage(&ul_context.uldev, 0x26, 0)){
        g_set_error_literal(error_, LD_NFC_ERROR, nfc_result, "Failed to write to NFC tag");
        goto lbl_finalize;
    }


    g_print("Finished. Tag was written successfully.\n");
    result = TRUE;
lbl_finalize:
    nfc_close(ul_context.nfcdev);
    nfc_exit(ul_context.nfcctx);
    return result;
} /* write */


int
main(int argc, char*argv[] ) {

    int status;
    GError *p_error = NULL;
    GOptionContext *opt_context = g_option_context_new ("- Lego Dimensions cli");
    g_option_context_set_summary(opt_context, "ldcli works on Near Field Communication Tags for the Lego Dimensions game.\n"
                                 "It can read, write tags and list brief information about known characters.\n"
                                 "Read and write operations depend on a preconfigured libnfc installation.");
    g_option_context_set_description(opt_context, "NFC tags of type NFC Sticker, 22mm, NTAG 213, 168 Byte were successfully tested.");
    g_option_context_add_main_entries(opt_context, optentries_main, NULL);

    GOptionGroup *optgrp_commands = g_option_group_new("command"
            , "Command Options :"
            , "Show command options"
            , &cli_args, NULL);
    g_option_group_add_entries(optgrp_commands, optentries_commands);
    g_option_group_set_parse_hooks(optgrp_commands, NULL, &post_parse_option_group_command_func);
    //g_option_context_set_main_group( opt_context, optgrp_commands);
    g_option_context_add_group(opt_context, optgrp_commands);

    g_option_context_parse(opt_context, &argc, &argv, &p_error);
    g_option_context_free(opt_context); opt_context = NULL;
    if ( p_error ) {
        g_printerr ("Option parsing failed: %s\nCall '%s --help-all' for detailed usage message.\n",
            p_error->message, g_path_get_basename (argv[0]));
        status = p_error->code;
        g_clear_error (&p_error);
    } else {
        g_assert(cli_args.command_func);
        if( FALSE == cli_args.command_func(&p_error)){
            g_assert(p_error);
            g_printerr ("Executing command failed: code(%d) message(%s)\n", p_error->code, p_error->message);
            status = p_error->code;
            g_clear_error (&p_error);
        }
    }
    return status;
} //main
