/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <gtk/gtk.h>
#include "gui.h"

G_MODULE_EXPORT void
cb_up_button_clicked( GtkButton *button_, AppContext *ctx_ )
{
    g_debug("UpButton clicked.\n");
    gui_show_previous_character(ctx_);
} // cp_up_button_clicked


G_MODULE_EXPORT void
cb_down_button_clicked( GtkButton *button_, AppContext *ctx_ )
{

    g_debug("DownButton clicked.\n");
    gui_show_next_character(ctx_);
} // cb_down_button_clicked


G_MODULE_EXPORT void
cb_record_button_clicked( GtkButton *button_, AppContext *ctx_ ){
    GtkWidget   *dialog;
    guint64      cid;
    const gchar *cname;
    g_print("RecordButton clicked.\n");
    g_assert(ctx_);

    gtk_tree_model_get(GTK_TREE_MODEL(ctx_->character_store), &ctx_->iter,
            COL_CHARACTER_ID, &cid,
            COL_DISPLAY_NAME, &cname,
            -1);

    dialog = gtk_message_dialog_new(
            ctx_->main_window, // GtkWindow *parent,
            GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT,  // GtkDialogFlags flags,
            GTK_MESSAGE_INFO,  // GtkMessageType type,
            GTK_BUTTONS_CANCEL,// GtkButtonsType buttons,
            "%03"G_GUINT64_FORMAT" - %s",    // const gchar *message_format,
            cid,
            cname
    );
    gtk_window_set_title(GTK_WINDOW(dialog), "Record character");

    g_signal_connect_swapped( dialog, "response", G_CALLBACK(gtk_widget_destroy), dialog);

    gtk_widget_show_all(dialog);
    gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), "Waiting for compatible NFC tag...");


} //
