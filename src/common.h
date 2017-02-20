
#ifndef HAVE_COMMON_H
#define HAVE_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <nfc/nfc.h>
#include <stdbool.h>

#include "ultralight.h"

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
	nfc_context *nfcctx;
	nfc_device  *nfcdev;
	ul_device    uldev;
	unsigned int startPage;
	unsigned int pageCount;
	bool lenient;
} app_ctx;

bool open_default_device(nfc_context ** retCtx, nfc_device ** retDev);
ul_result initialize(int argc, char ** argv, app_ctx * ctx);
void finalize(app_ctx * ctx);
size_t hex2bin(const char * string, uint8_t * bytes, size_t size);

#endif
