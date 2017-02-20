#include "ldnfc.h"
#include <glib.h>

#include "legodimensions.h"
#include "common.h"
GQuark
ld_nfc_error_quark (void)
{
  return g_quark_from_static_string ("ld-nfc-error-quark");
}

gboolean
ldnfc_open_tag( app_ctx *ctx_, GError **error_){
    guint32    ld_pwd;
    ul_result  ultralight_result;

    g_assert(ctx_);

    if (!open_default_device(&ctx_->nfcctx, &ctx_->nfcdev)) {
        g_set_error_literal(error_, LD_NFC_ERROR, UL_ERROR
            , "Unable to open nfc device. Please configure libnfc");
        return FALSE;
    }

    ul_result ret = ul_detect(ctx_->nfcdev, &ctx_->uldev);
    if (ret) {
        g_set_error_literal(error_, LD_NFC_ERROR, UL_NOTAG,"Unable to detect Ultralight tag");
        return FALSE;
    }

    g_print("Detected Ultralight NFC Tag\n");
    g_print(" - TAGID: ");

    unsigned int i;
    for (i = 0; i < ctx_->uldev.idSize; i++) {
        g_print("%02x", ctx_->uldev.id[i]);
    }
    g_print("\n");

    g_print(" - Model: %s\n - %d pages (%d bytes)\n - %d write-only password pages (%d bytes)\n",
        ctx_->uldev.type->name,
        ctx_->uldev.type->pages,
        ctx_->uldev.type->pages * UL_PAGSIZE,
        ctx_->uldev.type->passwordPages,
        ctx_->uldev.type->passwordPages * UL_PAGSIZE
    );
    if (ctx_->uldev.type->pages == 0) {
        g_set_error_literal(error_, LD_NFC_ERROR, UL_UNSUPPORTED, "Unsupported NFC tag model");
        return FALSE;
    }

    /* Test read procedure and authenticate if necessary */
    return ldnfc_enable_read(ctx_, error_);
} /* ldnfc_open_tag */


gboolean
ldnfc_enable_read(app_ctx *ctx_, GError **error_){
    ul_result ultralight_result;
    g_assert_nonnull(ctx_);
    ul_page read_buffer[UL_PAGSIZE];
    gboolean result = FALSE;

    ultralight_result = ul_read(&ctx_->uldev, 0x24, read_buffer);

    if ( NFC_ERFTRANS == ultralight_result ) {
        guint32 ld_pwd = ld_genpwd(ctx_->uldev.id);
        g_info("Regular reading failed. Retry with NTAG authentication PWD(%08x).", ld_pwd);

        ultralight_result = ul_detect(ctx_->nfcdev, &ctx_->uldev);
        if (ultralight_result) {
            g_set_error_literal(error_, LD_NFC_ERROR, UL_NOTAG,"Unable to detect Ultralight tag");
            return FALSE;
        }

        /* Write LD pwd to device structure.
           This enables NTAG213 authentication. */
        ctx_->uldev.hasKey = true;
        ctx_->uldev.key[3] = ld_pwd & 0xff;
        ld_pwd = ld_pwd >>8;
        ctx_->uldev.key[2] = ld_pwd & 0xff;
        ld_pwd = ld_pwd >>8;
        ctx_->uldev.key[1] = ld_pwd & 0xff;
        ld_pwd = ld_pwd >>8;
        ctx_->uldev.key[0] = ld_pwd & 0xff;


        ultralight_result = ul_read(&ctx_->uldev, 0x24, read_buffer);
    }

    if ( ultralight_result < 0) {
        g_set_error(error_, LD_NFC_ERROR, ultralight_result, "libnfc failed to authenticate NFC tag: %s"
                    , nfc_strerror( ctx_->nfcdev ));
    } else
    if ( ultralight_result > 0) {
        g_set_error_literal( error_, LD_NFC_ERROR, ultralight_result, "ul_read() failed.");
    } else {
        result = TRUE;
    }

    return result;
} /* libnfc_enable_read */



gboolean
ldnfc_read_two_pages(app_ctx *ul_context_, guint pageaddr_, guint32 *data0_, guint32 *data1_, GError **error_){
    ul_page read_buffer[UL_RDPAGS];
    ul_result ultralight_result;
    g_assert_nonnull(data0_);g_assert_nonnull(data1_);

    // Get page to distinguish between character and vehicle
    if( ultralight_result = ul_read(&ul_context_->uldev, pageaddr_, read_buffer)){
        g_set_error(error_, LD_NFC_ERROR, ultralight_result, "Failed to read from NFC tag. libnfc(%s)"
                    , nfc_strerror(ul_context_->uldev.nfc));
        return FALSE;
    }

    *data0_ = read_buffer[0][0]<<24 | read_buffer[0][1]<<16 | read_buffer[0][2]<<8| read_buffer[0][3];
    *data1_ = read_buffer[1][0]<<24 | read_buffer[1][1]<<16 | read_buffer[1][2]<<8| read_buffer[1][3];

    g_debug("%s(pageaddr_:0x%02x-0x%02x): 0x%08x 0x%08x", __func__, pageaddr_, pageaddr_+1, *data0_, *data1_);
    //g_debug("%s(pageaddr_:0x%02x): 0x%08x", __func__, pageaddr_+1, *data1_);

    return TRUE;
} /* ldnfc_read_two_pages */
