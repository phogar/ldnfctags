
#ifndef HAVE_ULTRALIGHT_H
#define HAVE_ULTRALIGHT_H

#include <stdbool.h>
#include <nfc/nfc.h>

typedef enum {
	UL_OK = 0,
	UL_ERROR = 1,
	UL_UNSUPPORTED = 2,
	UL_NOTAG = 3,
	UL_NOTULTRALIGHT = 4,
	UL_NEEDSPASS = 5,
	UL_WRONGPASS = 6,
	UL_PAGENX = 7
} ul_result;



#define UL_WRPAGS 1
#define UL_RDPAGS 4

#define UL_PAGSIZE 4
#define UL_SIGSIZE 32
#define UL_PACKSIZE 2

typedef uint8_t ul_page[UL_PAGSIZE];
typedef uint8_t ul_passack[UL_PACKSIZE];

typedef struct {
	const char * name;
	unsigned int pages;
	unsigned int passwordPages;
} ul_type;

typedef struct {
	nfc_device * nfc;
	ul_type const * type;
	size_t idSize;
	uint8_t id[16];
	bool hasKey;
	ul_page key;
	bool authed;
} ul_device;

ul_result ul_detect(nfc_device * nfcdev, ul_device * dev);
ul_result ul_select(ul_device * dev);
ul_result ul_write(ul_device * dev, unsigned int page, ul_page * data);
ul_result ul_writepage(ul_device *dev_, unsigned int page_, uint32_t data_);
ul_result ul_read(ul_device * dev, unsigned int page, ul_page * data);
ul_result ul_read_signature(ul_device * dev, uint8_t * data);
ul_result ul_set_key(ul_device * dev, const ul_page key);
ul_result ul_authenticate(ul_device * dev, const ul_page key, ul_passack pack);

#endif
