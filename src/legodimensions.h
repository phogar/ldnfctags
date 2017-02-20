#ifndef HAVE_LEGODIMENSIONS_H
#define HAVE_LEGODIMENSIONS_H

#include <glib.h>

#define LD_UID_BYTES 7

void
ld_encrypt(guint8 *uid_, guint32 charid_, guint32 *buf_);
guint32
ld_genpwd(const guint8 *uid_);

guint
ld_decrypt_character_pages(guint8 *uid_, guint32 *buf_);

guint
ld_decode_vehicle_id(guint32 *buf_ );


#endif
