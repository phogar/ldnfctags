#ifndef HAVE_LEGODIMENSION_CHARACTERS_H
#define HAVE_LEGODIMENSION_CHARACTERS_H

#include <glib.h>
#include "legodimensions_ntag.h"

// Last index of character array
//#define LD_MAX_KNOWN_CID 64
//#define LD_MAX_KNOWN_CID ( (int)sizeof(ld_characters)/sizeof(ld_characters[0]) )
#define LD_MAX_CID 99
#define LD_MIN_CID 1

#define LD_CID_VALID(cid) ( cid >= LD_MIN_CID && cid <= LD_MAX_CID )

/* List the different Worlds */

void
ld_print_characters();

void
ld_print_character_by_id(guint cid_);

const gchar *
ld_get_character_name_by_id( guint cid_, GError **error_);

const gchar *
ld_get_character_world_by_id( guint cid_, GError **error_);

const ntag_t *
ld_get_character_by_id( guint cid_, GError **error_);

#endif
