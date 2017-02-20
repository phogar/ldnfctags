
#include "common.h"

ul_result execute(app_ctx * ctx) {
	ul_page buffer[UL_WRPAGS];
	ul_result ret;

	unsigned int page = min(ctx->uldev.type->pages, ctx->startPage);
	unsigned int count = min(ctx->uldev.type->pages - page, ctx->pageCount);
	fprintf(stderr, "Writing %u pages starting at page 0x%02X (lenient: %s)\n", count, page, ctx->lenient ? "true" : "false");

	while (count > 0) {
		if (!fread(buffer, sizeof(buffer), 1, stdin)) {
			fprintf(stderr, "* End of input stream *\n");
			return UL_ERROR;
		}

		ret = ul_write(&ctx->uldev, page, buffer);
		if (ret) {
			fprintf(stderr, "* Error writing page 0x%02X (%d) *\n", page, ret);
			if (ctx->lenient == false || ret == UL_WRONGPASS) {
				return ret;
			}
		}

		page += UL_WRPAGS;
		count -= UL_WRPAGS;
	}

	return UL_OK;
}

int main(int argc, char ** argv) {
	app_ctx ctx;

	ul_result ret = initialize(argc, argv, &ctx);
	if (ret) {
		return ret;
	}

	ret = execute(&ctx);
	finalize(&ctx);

	return ret;
}
