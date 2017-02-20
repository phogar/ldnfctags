#ifndef HAVE_UTILS_H
#define HAVE_UTILS_H

#include <glib.h>


#define E_DOM            10020
#define E_CODE_ARGUMENTS 8
//#define UINT32_TO_PAGE
gchar *
g_to_hex (gpointer buffer, gsize buffer_length, char** dst_);

gchar *
strdup_hex(const guint8 *buffer_, size_t size_);

void
debug_hex( const char* prefix_, guint8* buffer_, size_t size_);

void
debug_hex32(const guint8 *buf_);

gint
xdigit_str_to_guint8( const char *str_, guint8 *buf_, guint buflen_, GError **err_ );


#endif
