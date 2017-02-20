
#include <stdio.h>
#include <getopt.h>
#include "common.h"

bool open_default_device(nfc_context ** retCtx, nfc_device ** retDev) {
	nfc_context * ctx;
	nfc_device * dev;

	nfc_init(&ctx);
	if (ctx == NULL) {
		perror("nfc_init");
		goto fail0;
	}

	dev = nfc_open(ctx, NULL);
	if (dev == NULL) {
		perror("nfc_open");
		goto fail1;
	}

	if (nfc_initiator_init(dev) < 0) {
		nfc_perror(dev, "nfc_initiator_init");
		goto fail2;
	}

	if (nfc_device_set_property_bool(dev, NP_INFINITE_SELECT, false) < 0) {
		nfc_perror(dev, "nfc_device_set_property_bool");
		goto fail2;
	}

	*retCtx = ctx;
	*retDev = dev;
	return true;

fail2:
	nfc_close(dev);
fail1:
	nfc_exit(ctx);
fail0:
	return false;
}

ul_result initialize(int argc, char ** argv, app_ctx * ctx) {
	if (!open_default_device(&ctx->nfcctx, &ctx->nfcdev)) {
		return UL_ERROR;
	}

	ul_page key;
	ul_result ret;
	unsigned int i;

	ret = ul_detect(ctx->nfcdev, &ctx->uldev);
	if (ret) {
		fprintf(stderr, "* Unable to detect Ultralight tag *\n");
		return ret;
	}

	fprintf(stderr, "Detected Ultralight\n");
	fprintf(stderr, " - UID:");
	for (i = 0; i < ctx->uldev.idSize; i++) {
		fprintf(stderr, " %02X", ctx->uldev.id[i]);
	}
	fprintf(stderr, "\n");

	fprintf(stderr, " - Model: %s\n - %d pages (%d bytes)\n - %d write-only password pages (%d bytes)\n", ctx->uldev.type->name, ctx->uldev.type->pages, ctx->uldev.type->pages * UL_PAGSIZE, ctx->uldev.type->passwordPages, ctx->uldev.type->passwordPages * UL_PAGSIZE);
	if (ctx->uldev.type->pages == 0) {
		fprintf(stderr, "* Unsupported model *\n");
		return UL_UNSUPPORTED;
	}

	ctx->startPage = 0;
	ctx->pageCount = ~0;
	ctx->lenient = false;
	while (true) {
		int c = getopt(argc, argv, "s:c:lk:");
		if (c == -1) {
			break;
		}

		switch (c) {
			case 's':
				ctx->startPage = strtoul(optarg, NULL, 0);
				break;

			case 'c':
				ctx->pageCount = strtoul(optarg, NULL, 0);
				break;

			case 'l':
				ctx->lenient = true;
				break;

			case 'k':
				hex2bin(optarg, key, UL_PAGSIZE);
				ul_set_key(&ctx->uldev, key);
				break;
		}
	}

	return UL_OK;
}

void finalize(app_ctx * ctx) {
	nfc_close(ctx->nfcdev);
	nfc_exit(ctx->nfcctx);
}

int hexchar2bin(char c) {
	if (c >= '0' && c <= '9') {
		return c - '0';
	}
	if (c >= 'A' && c <= 'F') {
		return c - 'A' + 0xA;
	}
	if (c >= 'a' && c <= 'f') {
		return c - 'a' + 0xA;
	}
	return -1;
}

size_t hex2bin(const char * string, uint8_t * bytes, size_t size) {
	int hi, lo;
	size_t read;

	for (read = 0; read < size; read++) {
		hi = hexchar2bin(string[read * 2 + 0]);
		if (hi < 0) {
			break;
		}

		lo = hexchar2bin(string[read * 2 + 1]);
		if (lo < 0) {
			break;
		}

		bytes[read] = hi << 4 | lo;
	}

	return read;
}	

