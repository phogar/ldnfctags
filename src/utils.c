#include "utils.h"

#include <glib.h>

gchar *
g_to_hex (gpointer buffer, gsize buffer_length, char** dst_) {
    char* ret = dst_&&*dst_?*dst_:g_malloc (buffer_length * 2 + 1);
    gsize i;
    for (i = 0; i < buffer_length; i++) {
        g_snprintf ((gchar *) (ret + i * 2), 3, "%02x", (guint) (*((guint8 *) (buffer + i))));
    }
    ret[buffer_length*2] = '\0';
    return ret;
}

gchar *
strdup_hex(const guint8 *buffer_, size_t size_){
    gchar *msg = g_strdup("");
    size_t i;
    for (i = 0; i < size_; i++){
        gchar *tmp = g_strdup_printf ("%s%02x", msg, buffer_[i]);
        g_free(msg);
        msg = tmp;
    }
    return msg;
}


void
debug_hex( const char* prefix_, guint8* buffer_, size_t size_)
{
    gchar *msg = strdup_hex(buffer_, size_);
    g_debug("%s%s", prefix_, msg);
    g_free(msg);
}


void
debug_hex32(const guint8 *buf_){
    g_debug("%02x%02x%02x%02x", buf_[0], buf_[1], buf_[2], buf_[3]);
}

gint
xdigit_str_to_guint8( const char *str_, guint8 *buf_, guint buflen_, GError **err_ )
{
    guint8      *p_dst = buf_;
    const gchar *p_src = str_;
    g_assert( NULL != p_dst  && NULL != p_src);

    while( *p_src && *(p_src+1) && p_dst < (buf_+buflen_)){
        // convert nibbles
        gint nibble_h = g_ascii_xdigit_value(*p_src);
        if( -1 == nibble_h ){
            g_set_error (err_, E_DOM, E_CODE_ARGUMENTS,
                "Invalid character. '%c' is not a hexadecimal number", *p_src);
            return 0;
        }
        p_src++;

        gint nibble_l = g_ascii_xdigit_value(*p_src);
        if( -1 == nibble_l ){
            g_set_error (err_, E_DOM, E_CODE_ARGUMENTS,
                "Invalid character. '%c' is not a hexadecimal number", *p_src);
            return 0;
        }
        p_src++;
        *p_dst++ = nibble_h<<4 | nibble_l;
    }
    return (p_dst-buf_)*2;
}// xdigit_str_to_guint8
