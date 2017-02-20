
#include "common.h"

ul_result execute(app_ctx * ctx) {
	ul_page buffer[UL_RDPAGS];
	ul_result ret;

	unsigned int page = min(ctx->uldev.type->pages - ctx->uldev.type->passwordPages, ctx->startPage);
	unsigned int count = min(ctx->uldev.type->pages - ctx->uldev.type->passwordPages - page, ctx->pageCount);
	fprintf(stderr, "Reading %u pages starting at page %02X\n", count, page);

	while (count > 0) {
		unsigned int printpags = min(count, UL_RDPAGS);

		ret = ul_read(&ctx->uldev, page, buffer);
		if (ret) {
			fprintf(stderr, "* Unexpected error while reading tag (pages 0x%02X ~ 0x%02X) *\n", page, page + UL_RDPAGS - 1);
			if (!ctx->lenient) {
				return ret;
			}

			buffer[0][0] = 0xDE;
			buffer[0][1] = 0xAD;
			buffer[0][2] = 0xBE;
			buffer[0][3] = 0xEF;
			printpags = 1;
		}

		if (fwrite(buffer, UL_PAGSIZE, printpags, stdout) != printpags) {
			fprintf(stderr, "* Unexpected end of output stream *\n");
			return UL_ERROR;
		}

		page += printpags;
		count -= printpags;
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
