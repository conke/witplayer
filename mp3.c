#include "mp3.h"

u8 *get_mp3_tag_buff(struct fifo *fifo, size_t *size)
{
	// fixme!
	return NULL;
}

int release_tag_buff(u8 *buff)
{
	// fixme!
	return 0;
}

int parse_mp3_tag(u8 *buff, size_t size, u8 **lrc, size_t *lrc_size, u8 **icon, size_t *icon_size)
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
	// fixme!
	return NULL;
}

int decode_close(struct decode *dec)
{
	// fixme!
	return 0;
}

int decode(struct decode *dec, u8 *raw_buff, size_t *raw_size, u8 *mp3_buff, size_t mp3_size)
{
	// fixme!
	return 0;
}
