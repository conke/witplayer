#include "mp3.h"
#include "mpaudec.h"
#include <stdlib.h>

int parse_mp3_tag(struct sound_file_info *ifno, u8 **lrc, size_t *lrc_size, u8 **icon, size_t *icon_size)
{
	// fixme!

	return 0;
}

int get_mp3_param(struct decode *dec, u8 *buff, size_t size, struct mp3_param *param)
{
	// fixme!
	return 0;
}

struct decode *decode_open(decode_type_t type)
{
	struct decode *dec;

	dec = malloc(sizeof(*dec));
	if (dec == NULL) {
		perror("malloc");
		return NULL;
	}

	dec->type = type;

	switch (type) {
	case MPAUDEC:
		dec->dec = mpaudec_open();
		break;
	case GSTREAMERDEC:
		dec->dec = NULL;
		break;
	}

	return dec;
}

int decode_close(struct decode *dec)
{
	switch (dec->type) {
	case MPAUDEC:
		mpaudec_close(dec->dec);
		break;
	case GSTREAMERDEC:
		break;
	}

	free(dec);

	return 0;
}

int decode(struct decode *dec, u8 *raw_buff, size_t *raw_size, u8 *mp3_buff, size_t mp3_size)
{
	if (dec->type == MPAUDEC) {
		return mpaudec_decode_frame(dec->dec, raw_buff, (int *)raw_size, mp3_buff, mp3_size);
	}

	return 0;
}
