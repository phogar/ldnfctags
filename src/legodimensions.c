#include "legodimensions.h"
#include "legodimensions_characters.h"
#include "utils.h"
#include "tea.h"

#include <glib.h>
#include <string.h>


#define ROTR32(a,b)  ((a>>b)|(a<<(32-b)))


guint32
ld_scramble(const guint8 *uid_, guint cnt_){
    guint8 base[] = {
        0xFF, 0xFF, 0xFF, 0xFF,\
        0xFF, 0xFF, 0xFF, 0xb7,\
        0xd5, 0xd7, 0xe6, 0xe7,\
        0xba, 0x3c, 0xa8, 0xd8,\
        0x75, 0x47, 0x68, 0xcf,\
        0x23, 0xe9, 0xfe, 0xaa \
    };
    g_assert(cnt_>0 && cnt_<=8 && NULL!=uid_);
    memcpy(base, uid_, LD_UID_BYTES);
    base[(cnt_ * 4) - 1] = 0xaa;

    debug_hex("ld_scramble() base: ", base, 32);

    g_debug("%s():  i      v4       v5       b       v2", __FUNCTION__);
    guint32 v2 = 0;
    int i;
    for ( i = 0; i<cnt_; i++){
        guint32 v4 = ROTR32(v2,25);
        guint32 v5 = ROTR32(v2,10);
        guint32 b  = base[i*4+3]<< 24|
                      base[i*4+2]<< 16|
                      base[i*4+1]<< 8 |
                      base[i*4];
        v2 = (b + v4 + v5 -v2);

        g_debug("%s(): [%d] %08x %08x %08x %08x",__FUNCTION__, i, v4 , v5, b, v2);
    }

    return GUINT32_FROM_BE( v2 );
} // ld_scramble


void
ld_genteakey(const guint8 *uid_, guint32 *p_key_){
    g_assert(NULL != uid_ && NULL != p_key_);
    p_key_[0] = ld_scramble(uid_,3);
    p_key_[1] = ld_scramble(uid_,4);
    p_key_[2] = ld_scramble(uid_,5);
    p_key_[3] = ld_scramble(uid_,6);

    gchar *uid_ascii = strdup_hex(uid_, LD_UID_BYTES);
    g_debug("%s(uid:%s) return(%08x %08x %08x %08x)", __FUNCTION__, uid_ascii, p_key_[0], p_key_[1], p_key_[2], p_key_[3]);
    g_free(uid_ascii);

} // ld_genteakey



// guint8 *uid_ 7 bytes long
guint32
ld_genpwd(const guint8 *uid_) {
    guint8 base[] = "UUUUUUU(c) Copyright LEGO 2014AA"; // 32 bytes buffer
    g_assert( NULL != uid_ );
    memcpy(base, uid_, LD_UID_BYTES);
    guint32 v2 = 0, result = 0;
    base[30] = base[31] = 0xaa;
    debug_hex("ld_genpwd() base: ", base, 32);

    g_debug("%s()  i      v4       v5       b       v2", __FUNCTION__);
    int i;
    for ( i = 0; i<8; i++){
        guint32 v4 = ROTR32(v2,25);
        guint32 v5 = ROTR32(v2,10);
        guint32 b  = base[i*4+3]<< 24|
                      base[i*4+2]<< 16|
                      base[i*4+1]<< 8 |
                      base[i*4];
        v2 = (b + v4 + v5 -v2);

        g_debug("%s()[%d] %08x %08x %08x %08x",__FUNCTION__, i, v4 , v5, b, v2);
    }

    result = GUINT32_FROM_BE( v2 );
    g_debug("%s(tagid) return(%08x)", __func__, result);
    return result;
} // ld_genpwd



/** \brief
 *
 * \param uid_ - 7byte (LD_UID_BYTES) long buffer with NFC Tag UID
 * \param buf_ - 2x4 byte long buffer with encrypted character info from NFC tag page 0x24, 0x25
 * \return id of lego dimension character
 *
 */
guint
ld_decrypt_character_pages(guint8 *uid_, guint32 *buf_){
    guint32 teakey[4];
    g_assert(uid_ || buf_);
    guint result;

    gchar *uid_ascii = strdup_hex(uid_, LD_UID_BYTES);
    g_debug("%s(uid:%s,buf:%08x%08x)",
        __func__, uid_ascii, buf_[0], buf_[1]);

    ld_genteakey(uid_, teakey);


    //guint32 key[4];
    teakey[0] = GUINT32_FROM_BE(teakey[0]);
    teakey[1] = GUINT32_FROM_BE(teakey[1]);
    teakey[2] = GUINT32_FROM_BE(teakey[2]);
    teakey[3] = GUINT32_FROM_BE(teakey[3]);

    buf_[0] = GUINT32_FROM_BE(buf_[0]);
    buf_[1] = GUINT32_FROM_BE(buf_[1]);

    tea_decrypt(buf_, teakey);


    if ( buf_[0] != buf_[1]){
        g_debug("%s(uid:%s): return(0) - decrypted pages: %08x, %08x are not identical! Tag has invalid data."
                , __func__, uid_ascii, buf_[0], buf_[1]);
        result = 0;
        goto lbl_cleanup;
    }
    g_debug("%s(uid:%s): - decrypted pages: %08x, %08x", __func__, uid_ascii, buf_[0], buf_[1]);

    g_assert_cmpint( buf_[0], ==, buf_[1] );
    result = buf_[0];
    //buf_[0] = GUINT32_FROM_BE(buf_[0]);
    //result = GUINT32_FROM_BE(buf_[0]);
    g_debug("%s(uid:%s): return(%d)", __func__, uid_ascii, result);

lbl_cleanup:
    g_free(uid_ascii);
    return result;
} /* ld_decrypt */



guint
ld_decode_vehicle_id(guint32 *buf_ ){
    g_assert_nonnull(buf_);

    return GUINT32_FROM_BE( *buf_ )-1000;
} /* ld_decode_vehicle_id */



//
// guint8  *uid_ 7 bytes long
// guint32 *buf_ 2x4 bytes long
//
void
ld_encrypt(guint8 *uid_, guint32 charid_, guint32 *buf_){
    guint32 teakey[4];
    g_assert( NULL != uid_ && NULL != buf_);
    ld_genteakey(uid_, teakey );
    buf_[0] = buf_[1] = GUINT32_TO_LE(charid_);

    gchar *uid_ascii = strdup_hex(uid_, LD_UID_BYTES);
    g_debug("%s(uid:%s,charid:%u): buf_pre(%08x%08x)",
        __FUNCTION__, uid_ascii, charid_, buf_[0], buf_[1]);

    guint32 key[4];
    key[0] = GUINT32_TO_BE(teakey[0]);
    key[1] = GUINT32_TO_BE(teakey[1]);
    key[2] = GUINT32_TO_BE(teakey[2]);
    key[3] = GUINT32_TO_BE(teakey[3]);

    tea_encrypt(buf_, key);

    buf_[0] = GUINT32_TO_BE(buf_[0]);
    buf_[1] = GUINT32_TO_BE(buf_[1]);


    g_debug("%s(uid:%s,charid:%u): key(%08x %08x %08x %08x) encrypted_buffer(%08x %08x)",
        __FUNCTION__, uid_ascii, charid_, key[0], key[1], key[2], key[3], buf_[0], buf_[1]);
    g_free(uid_ascii);
} // ld_encrypt
