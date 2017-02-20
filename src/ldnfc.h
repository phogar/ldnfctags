#ifndef HAVE_LDNFC_H
#define HAVE_LDNFC_H

#include <glib.h>
#include "common.h"

#define LD_NFC_ERROR ld_nfc_error_quark ()

GQuark
ld_nfc_error_quark (void);

gboolean
ldnfc_open_tag( app_ctx *ctx_, GError **error_);

gboolean
ldnfc_enable_read(app_ctx *ctx_, GError **error_);

gboolean
ldnfc_read_two_pages(app_ctx *ul_context_, guint pagenr_, guint32 *page0_, guint32 *page1_, GError **error_);
#endif
