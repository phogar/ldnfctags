#include <getopt.h>
#include <stdlib.h>
//#include <string.h>
#include <glib.h>
#include <glib/gprintf.h> 
#include "legodimensions.h"
#include "utils.h"




int main(int argc, char ** argv)
{
    GError *err = NULL;

    guint8  uid[LD_UID_BYTES];
    guint32 charid = 0;
    gint converted = 0;
    while (1) {
        gchar *eptr=NULL;
        int c = getopt(argc, argv, "u:c:");
            if (c == -1) {
		break;
            }
	switch (c) {
            case 'u':
                converted = xdigit_str_to_guint8(optarg, uid, LD_UID_BYTES, &err );
                if( NULL != err){ goto GERROR; }
                if ( converted != LD_UID_BYTES*2 ){
                    g_set_error (&err, E_DOM, E_CODE_ARGUMENTS,
                    "Converted %d characters. But input must have %d characters.", converted, LD_UID_BYTES*2);
                    goto GERROR;
                }
            break;
            case 'c':
                charid = g_ascii_strtoull (optarg, &eptr, 0);
                if ( eptr == optarg) {
                    g_set_error (&err, E_DOM, E_CODE_ARGUMENTS,
                    "Could not parse character id '%s'.",optarg);
                    goto GERROR;
                }          
            break;
        default:
            goto USAGE;
        }
    }
    if (!converted) goto USAGE;

   
    if ( charid  ){
        guint32 pages[2];
        ld_encrypt(uid, charid, pages);
        g_printf("[0x24]%08x [0x25]%08x ", pages[0], pages[1]);
    }

    guint32 rslt = ld_genpwd(uid);
    g_printf("[0x2b]%08x", rslt);

    g_printf("\n");
    return 0;

GERROR:
    g_fprintf(stderr, "%s\n", err->message);
    g_error_free(err);
    exit(EXIT_FAILURE);
USAGE:
   g_fprintf(stderr, "Usage: %s -u <7 byte uid in HEX>\n", g_path_get_basename (argv[0]));
   exit(EXIT_FAILURE);
} // main
