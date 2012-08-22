#pragma once
#include <stdio.h>
#include "types.h"

typedef enum {
	MPAUDEC,
	GSTREAMERDEC
} decode_type_t;

struct mp3_param {
	int format;
	int channels;
	int bits_per_sample;
};

struct decode {
	decode_type_t type;
	void *dec;
};

int parse_mp3Tag(u8 *buff, size_t size, u8 *lrc, u8 *icon);
int get_mp3_param(struct decode *dec, u8 *buff, size_t size, struct mp3_param *param);
struct decode *decode_open(decode_type_t type);
int decode_close(struct decode *dec);
size_t decode(struct decode *dec, u8 *raw_buff, size_t *raw_size, u8 *mp3_buff, size_t mp3_size);
