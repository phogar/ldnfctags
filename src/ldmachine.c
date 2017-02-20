
/*
 *  * Compile me with:
 *   *   gcc -o tut tut.c $(pkg-config --cflags --libs gtk+-3.0 gmodule-2.0)
 *    */
#include <glib.h>
#include <gtk/gtk.h>
#include "gui.h"
#include "config.h"


// Splits the Character Image Filename by '_' and uses the parts as dataset.
// Eg.  010_Cole_Ninjago_168.png
// 010     - Character ID
// Cole    - Display Name of Character
// Ninjago - Name of the world the character belongs to.
// The image itself gets loader as  GdkPixbuf
gboolean
add_character_to_store_from_file_info(GFileInfo *finfo_, GtkListStore *store_, GtkTreeIter *iter_, GError **err_){
    gchar const *fname;      // filename
    gchar       *path;   // absolute filepath
    gchar       *cname;  // Name of character
    gchar       *cworld; // Name of World the character belongs to
    gchar       *c;
    guint64      cid;    // NFC Tag Id of character
    gchar      **dset;   // '_' splitted filename. e.g. 010 / Cole / 168.png
    gchar       *endptr = NULL;
    GdkPixbuf   *pixbuf;
    gboolean     result = FALSE;

    fname = g_file_info_get_name(finfo_);
    dset = g_strsplit (fname, "_", 4);
    if ( !dset || !dset[0]){
        g_set_error(err_, G_FILE_ERROR, 1 , "Character Image filename '%s' schema mismatch. Could not split by '_'. Skipping!", fname );
        goto failed1;
    }

    // Check character ID
    cid = g_ascii_strtoull (dset[0], &endptr, 10 );
    if ( !endptr ) {
        g_set_error(err_, G_FILE_ERROR, 1 , "Character Image filename '%s' does not begin with character id.  Skipping!", fname );
        goto failed1;
    }

    // Check character name
    if( !dset[1] ){
        g_set_error(err_, G_FILE_ERROR, 1 , "Character Image filename '%s' does not have an name part. Skipping!", fname );
        goto failed1;
    }
    c = dset[1];
    do{if(*c=='-') *c= ' ';}while(*++c);
    cname = dset[1];

    // Check world name
    if( !dset[2]){
        g_set_error(err_, G_FILE_ERROR, 1 , "Character Image filename '%s' does not have an world part. Skipping!", fname );
        goto failed1;
    }
    c = dset[2];
    do{if(*c=='-') *c= ' ';}while(*++c);
    cworld = dset[2];

    // Load file itself as image
    path = g_build_filename(CFG_IMAGE_DIR, fname, NULL);
    pixbuf = gdk_pixbuf_new_from_file_at_size (path, 240, 240, err_);
    g_assert(pixbuf);

    g_info("Appending file '%s' as character id(%"G_GUINT64_FORMAT") name(%s) world(%s).", path, cid, cname, cworld);
    gtk_list_store_append (store_, iter_);

    gtk_list_store_set (store_, iter_,
        COL_CHARACTER_ID, cid,
        COL_DISPLAY_NAME, cname,
        COL_WORLD_NAME,   cworld,
        COL_PIXBUF,       pixbuf,
        -1);

    result = TRUE;
    g_object_unref (pixbuf);
    g_free(path);

failed1:
    g_strfreev(dset);
    return result;
} // add_character_to_store_from_file_info

void
fill_characterstore(AppContext *ctx_, GError **err_){
    GtkTreeIter     iter;
    GFile           *img_dir;
    GFileEnumerator *img_enum;
    GFileInfo       *finfo;
    GtkListStore    *store;

    g_assert(ctx_);
    store = ctx_->character_store;
    gtk_list_store_clear(store);
    ctx_->num_images = 0;
    img_dir  = g_file_new_for_path(CFG_IMAGE_DIR);
    img_enum = g_file_enumerate_children (img_dir,
                           G_FILE_ATTRIBUTE_STANDARD_NAME,
                           G_FILE_QUERY_INFO_NONE,
                           NULL,
                           err_);
    g_assert(img_enum);
    g_object_unref(img_dir);

    while( finfo = g_file_enumerator_next_file(img_enum, NULL, err_)){
        GError *internal_err = NULL;
        const char*fn;
        GFileType ft = g_file_info_get_file_type(finfo);
        switch( ft ){
            case G_FILE_TYPE_REGULAR:
                if(add_character_to_store_from_file_info(finfo, store, &iter, &internal_err)){
                    ctx_->num_images++;
                } else {
                    g_printerr ("%s", internal_err->message);
                    g_error_free(internal_err); internal_err = NULL;
                }
            break;
            case G_FILE_TYPE_DIRECTORY:
            break;
            default:
                g_debug("Unknown filetype: %d", ft);
        }
        g_object_unref(finfo);
    }
    g_object_unref(img_enum);

    gtk_tree_sortable_set_sort_column_id( (GtkTreeSortable*)store // GtkTreeSortable *sortable,
                                          , 0   // gint sort_column_id,
                                          , GTK_SORT_ASCENDING //GtkSortType order
                                      );
} // fill_iconview


int
main(int argc, char **argv) {
    AppContext   ctx;
    GtkBuilder   *builder;

    GdkPixbuf    *pixbuf;
    GError       *error = NULL;

    /* Init GTK+ */
    gtk_init(&argc, &argv);

    /* Create new GtkBuilder object */
    builder = gtk_builder_new();
    /* Load UI from file. If error occurs, report it and quit application.
     *      * Replace "tut.glade" with your saved project. */
    if (!gtk_builder_add_from_resource(builder, "/ldnfcgui/gui/ldnfcgui.glade", &error)) {
        g_warning("%s", error->message);
        g_error_free(error);
        return ( 1);
    }

    /* Get main window pointer from UI */
    ctx.main_window = GTK_WINDOW(gtk_builder_get_object(builder, "main_window"));
    ctx.main_image  = GTK_IMAGE(gtk_builder_get_object(builder, "main_image"));
    ctx.label       = GTK_LABEL(gtk_builder_get_object(builder, "label"));

    ctx.character_store  = gtk_list_store_new (NUM_COLS, G_TYPE_UINT64, G_TYPE_STRING, G_TYPE_STRING, GDK_TYPE_PIXBUF);
    fill_characterstore(&ctx, &error);

    gui_show_first_character(&ctx);

    /* Connect signals */
    gtk_builder_connect_signals(builder, &ctx);

    /* Destroy builder, since we don't need it anymore */
    g_object_unref(G_OBJECT(builder));

    /* Show window. All other widgets are automatically shown by GtkBuilder */
    gtk_widget_show(GTK_WIDGET(ctx.main_window));

    /* Start main loop */
    gtk_main();

    return (0);
} // main
