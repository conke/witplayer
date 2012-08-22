#pragma once
#include <stdio.h>
#include "fifo.h"
#include "types.h"

typedef enum {
	MPAUDEC,
	GSTREAMERDEC
} decode_type_t;

struct mp3_param {
	int rate;
	int channels;
	int bits_per_sample;
};

struct decode {
	decode_type_t type;
	void *dec;
};

u8 *get_mp3_tag_buff(struct fifo *fifo, size_t *size);
int release_tag_buff(u8 *buff);
int parse_mp3_tag(u8 *buff, size_t size, u8 **lrc, size_t *lrc_size, u8 **icon, size_t *icon_size);
int get_mp3_param(struct decode *dec, u8 *buff, size_t size, struct mp3_param *param);
struct decode *decode_open(decode_type_t type);
int decode_close(struct decode *dec);
int decode(struct decode *dec, u8 *raw_buff, size_t *raw_size, u8 *mp3_buff, size_t mp3_size);
