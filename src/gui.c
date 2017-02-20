/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "gui.h"

void 
gui_show_first_character(AppContext *ctx_){
   g_assert(ctx_);
    
   gtk_tree_model_get_iter_first(GTK_TREE_MODEL(ctx_->character_store), &ctx_->iter );
   ctx_->image_index = 1;
   gui_update_character(ctx_); 
} // gui_show_first_character

void
gui_show_previous_character(AppContext *ctx_){
    GtkTreePath *path;
    g_assert(ctx_);
    
    path = gtk_tree_model_get_path(GTK_TREE_MODEL(ctx_->character_store), &ctx_->iter);
    if (gtk_tree_path_prev (path)) {
        gtk_tree_model_get_iter(GTK_TREE_MODEL(ctx_->character_store), &ctx_->iter, path);
        ctx_->image_index--;
    } else {
        GtkTreeIter iter = ctx_->iter;
        while(gtk_tree_model_iter_next(GTK_TREE_MODEL(ctx_->character_store), &iter)){
            ctx_->iter = iter;
        }
        ctx_->image_index = ctx_->num_images;
    }
    
    gui_update_character(ctx_);
    gtk_tree_path_free(path);
} // gui_show_previous_character


void
gui_show_next_character(AppContext *ctx_){
    g_assert(ctx_);
    if (gtk_tree_model_iter_next(GTK_TREE_MODEL(ctx_->character_store), &ctx_->iter)){
        ctx_->image_index++;
        gui_update_character(ctx_);
    } else {
        gui_show_first_character(ctx_);
    }
    
} // gui_show_next_character


void 
gui_update_character(AppContext *ctx_){
    GdkPixbuf   *pixbuf;
    const gchar *cname;
    const gchar *cworld;
    gchar       *msg;
    g_assert(ctx_);

    gtk_tree_model_get(GTK_TREE_MODEL(ctx_->character_store), &ctx_->iter, 
            COL_PIXBUF, &pixbuf,
            COL_DISPLAY_NAME, &cname,
            COL_WORLD_NAME, &cworld, 
            -1);
    
    gtk_image_set_from_pixbuf(ctx_->main_image, pixbuf);
    msg = g_strdup_printf("%s\n%s\n%d/%d", cname, cworld, ctx_->image_index, ctx_->num_images);
    gtk_label_set_text(ctx_->label, msg );        
    g_free(msg);
} // gui_update_character
