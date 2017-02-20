
#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "ultralight.h"

#define array_size(x) (sizeof(x) / sizeof(x[0]))

static const nfc_modulation MIFARE_MODULATION = {
	.nmt = NMT_ISO14443A,
	.nbr = NBR_106
};

typedef struct {
	version_response response;
	ul_type type;
} response_and_type;

static const ul_type PLAIN_ULTRALIGHT = { "Ultralight", 16, 0 };
static const ul_type UNKNOWN_ULTRALIGHT = { "Unknown version", 0, 0 };

static const response_and_type KNOWN_ULTRALIGHTS_VERSIONS[] = {
	{ { 0x00, 0x04, 0x04, 0x02, 0x01, 0x00, 0x0F, 0x03 }, { "NTAG213",  45, 2 } },
	{ { 0x00, 0x04, 0x04, 0x02, 0x01, 0x00, 0x11, 0x03 }, { "NTAG215", 135, 2 } },
	{ { 0x00, 0x04, 0x04, 0x02, 0x01, 0x00, 0x13, 0x03 }, { "NTAG216", 231, 2 } }
};

ul_result identify(ul_device * dev);

ul_result ul_detect(nfc_device * nfcdev, ul_device * dev) {
	nfc_target target;

	if (nfc_initiator_select_passive_target(nfcdev, MIFARE_MODULATION, NULL, 0, &target) <= 0) {
		return UL_NOTAG;
	}

	if (target.nti.nai.abtAtqa[0] != 0x00 || target.nti.nai.abtAtqa[1] != 0x44) {
		return UL_NOTULTRALIGHT;
	}

	size_t idSize = target.nti.nai.szUidLen;
	memcpy(dev->id, &target.nti.nai.abtUid, idSize);
	dev->idSize = idSize;
	dev->nfc = nfcdev;
	dev->hasKey = false;
	dev->authed = false;

	return identify(dev);
}

ul_result ul_select(ul_device * dev) {
	nfc_target target;

	if (nfc_initiator_select_passive_target(dev->nfc, MIFARE_MODULATION, dev->id, dev->idSize, &target) <= 0) {
		return UL_NOTAG;
	}

	dev->authed = false;

	return UL_OK;
}

ul_result transceive(ul_device * dev, const void * req, size_t reqlen, void * resp, size_t resplen, bool isData) {
	if (nfc_device_set_property_bool(dev->nfc, NP_EASY_FRAMING, isData) < 0) {
		nfc_perror(dev->nfc, "nfc_device_set_property_bool");
		return UL_ERROR;
	}

	ul_result ret = UL_OK;
	int code = nfc_initiator_transceive_bytes(dev->nfc, req, reqlen, resp, resplen, -1);
	if (code < 0) {
        return code;
		ret = ul_select(dev);
		if (ret == UL_OK) {
			ret = UL_UNSUPPORTED;
		}
        else {
			nfc_perror(dev->nfc, "nfc_initiator_transceive_bytes");
		}
	}

	return ret;
}

ul_result ul_write(ul_device * dev, unsigned int page, ul_page * data) {
	write_request req;
	ul_result res;

	if (dev->hasKey && !dev->authed) {
		res = ul_authenticate(dev, dev->key, NULL);
		if (res != UL_OK) {
			return res;
		}
	}

	req.command = CMD_WRITE;
	req.address = page;
	memcpy(req.data, data, UL_PAGSIZE * UL_WRPAGS);

	// TODO: Check why I need to send data twice so I get errors on failed writes
	res = transceive(dev, &req, sizeof(req), NULL, 0, true);
	res = transceive(dev, &req, sizeof(req), NULL, 0, true);

	return res;
}

ul_result
ul_writepage(ul_device *dev_, unsigned int page_, uint32_t data_){
    ul_page data[1];
    data[0][0] = data_ >> 24;
    data[0][1] = data_ >> 16;
    data[0][2] = data_ >> 8 ;
    data[0][3] = data_;
    printf(" - Writing 0x%08x to page 0x%02x...", data_, page_ );
    ul_result result = ul_write(dev_, page_, data);
    if ( result ) {
        printf("failed! Exit(%d)\n", result);
    } else {
        printf("done.\n");
    }
    return result;
} // ul_writepage


ul_result ul_read(ul_device * dev, unsigned int page, ul_page * data) {
	read_request req;
	ul_result res;

	if (dev->hasKey && !dev->authed) {
		res = ul_authenticate(dev, dev->key, NULL);
		if (res != UL_OK) {
			return res;
		}
	}

	req.command = CMD_READ;
	req.address = page;

	return transceive(dev, &req, sizeof(req), data, UL_PAGSIZE * UL_RDPAGS, true);
}

ul_result ul_read_signature(ul_device * dev, uint8_t * signature) {
	signature_request req;

	req.command = CMD_READ_SIG;
	req.address = 0;

	return transceive(dev, &req, sizeof(req), signature, UL_SIGSIZE, false);
}

ul_result ul_authenticate(ul_device * dev, const ul_page key, ul_passack pack) {
	auth_request req;

	req.command = CMD_PWD_AUTH;
	memcpy(req.key, key, UL_PAGSIZE);

	ul_result ret = transceive(dev, &req, sizeof(req), pack, UL_PACKSIZE, false);
	if (ret == UL_OK) {
		dev->authed = true;
	}

	return ret;
}

ul_result ul_set_key(ul_device * dev, const ul_page key) {
	if (dev->hasKey == true && memcmp(dev->key, key, UL_PAGSIZE) == 0) {
		return UL_OK;
	}

	dev->hasKey = true;
	memcpy(dev->key, key, UL_PAGSIZE);
	dev->authed = false;

	return UL_OK;
}

ul_result identify(ul_device * dev) {
	version_request req;
	version_response resp;
	unsigned int i;

	req.command = CMD_GET_VERSION;

	ul_result ret = transceive(dev, &req, sizeof(req), &resp, sizeof(resp), false);
	if (ret) {
		if (ret == UL_UNSUPPORTED) {
			dev->type = &PLAIN_ULTRALIGHT;
			return UL_OK;
		}

		return ret;
	}

	for (i = 0; i < array_size(KNOWN_ULTRALIGHTS_VERSIONS); i++) {
		if (memcmp(&KNOWN_ULTRALIGHTS_VERSIONS[i].response, &resp, sizeof(resp)) == 0) {
			dev->type = &KNOWN_ULTRALIGHTS_VERSIONS[i].type;
			return UL_OK;
		}
	}

	dev->type = &UNKNOWN_ULTRALIGHT;
	return UL_OK;
}
