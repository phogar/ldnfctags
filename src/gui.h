/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#ifndef GUICALLBACKS_H
#define GUICALLBACKS_H
#include <gtk/gtk.h>
#ifdef __cplusplus
extern "C" {
#endif


enum { 
    COL_CHARACTER_ID,
    COL_WORLD_NAME,
    COL_DISPLAY_NAME,
    COL_PIXBUF,
    NUM_COLS
};


    
// Structure to send through all signals / slots
typedef struct _AppContext AppContext;
struct _AppContext {
    GtkListStore *character_store;
    GtkTreeIter   iter;
    GtkImage     *main_image;
    GtkLabel     *label;
    GtkWindow    *main_window;
    uint          image_index;
    uint          num_images;
};
 
void 
gui_show_first_character(AppContext *ctx_);
void
gui_show_previous_character(AppContext *ctx_);
void
gui_show_next_character(AppContext *ctx_);

    
void 
gui_update_character(AppContext *ctx_);


#ifdef __cplusplus
}
#endif

#endif /* GUICALLBACKS_H */

