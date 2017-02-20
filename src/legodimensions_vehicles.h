#ifndef HAVE_LEGODIMENSION_VEHICLES_H
#define HAVE_LEGODIMENSION_VEHICLES_H
#include "legodimensions_ntag.h"

#include <glib.h>

// Last index of character array
#define LD_MIN_VID 0
#define LD_MAX_VID 999
#define LD_VID_VALID(vid) ( vid >= LD_MIN_VID && vid <= LD_MAX_VID )


void
ld_print_vehicles();
void
ld_print_vehicle_by_id(guint vehicle_id_);

const ntag_t *
ld_get_vehicle_by_id( guint cid_, GError **error);

#endif
