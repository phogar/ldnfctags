
#ifndef HAVE_STRUCTS_H
#define HAVE_STRUCTS_H

#include <stdint.h>
#include "ultralight.h"

enum {
	CMD_PWD_AUTH	= 0x1B,
	CMD_READ	= 0x30,
	CMD_READ_CNT	= 0x39,
	CMD_FAST_READ	= 0x3A,
	CMD_READ_SIG	= 0x3C,
	CMD_GET_VERSION	= 0x60,
	CMD_COMP_WRITE	= 0xA0,
	CMD_WRITE	= 0xA2,
};

#pragma pack(1)

typedef struct {
	uint8_t command;
	uint8_t address;
} read_request;

typedef struct {
	uint8_t command;
	uint8_t address;
	ul_page data[UL_WRPAGS];
} write_request;

typedef struct {
	uint8_t command;
} version_request;

typedef struct {
	uint8_t command;
	ul_page key;
} auth_request;

typedef struct {
	uint8_t header;
	uint8_t vendor;
	uint8_t type;
	uint8_t subtype;
	uint8_t majorVersion;
	uint8_t minorVersion;
	uint8_t size;
	uint8_t protocol;
} version_response;

typedef struct {
	uint8_t command;
	uint8_t address;
} signature_request;

#pragma pack()

#endif
