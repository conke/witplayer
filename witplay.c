#include <errno.h>
#include <stdio.h>
#include <pthread.h>
#include "witplay.h"

#define LOAD_BUFF (200 * 1024)
#define MP3_BUFF_SIZE 4096
#define RAW_BUFF_SIZE 4096

struct load_thread_arg {
	struct sound_file_info *file;
	struct fifo *fifo;
};

static void *load_to_fifo(void *arg)
{
	struct sound_file_info *file;
	struct fifo *fifo;
	u8 buff[LOAD_BUFF];
	size_t size;

	file = ((struct load_thread_arg *)arg)->file;
	fifo = ((struct load_thread_arg *)arg)->fifo;

	while (1) {
		size = sound_file_load(file, buff, LOAD_BUFF);
		if (size == 0)
			break;

		fifo_write(fifo, buff, size);
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	int ret;
	const char *url;
	struct sound_file_info *file;
	struct decode *dec;
	struct fifo *fifo;
	pthread_t tid;
	struct load_thread_arg arg;
	u8 *lrc;
	u8 *icon;
	size_t lrc_size;
	size_t icon_size;
	size_t tag_size;
	size_t size;
	u8 mp3_buff[MP3_BUFF_SIZE];
	u8 raw_buff[RAW_BUFF_SIZE];
	size_t mp3_size, raw_size;
	struct mp3_param mp3_pm;
	struct audio_output *out;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s PATH\n", argv[0]);
		return -EINVAL;
	}

	url = argv[1];

	file = sound_file_open(url);
	if (NULL == file) {
		return -ENODEV;
	}

	fifo = fifo_open();
	if (NULL == fifo) {
		goto L1;
		ret = -ENOMEM;
	}

	ret = parse_mp3_tag(file, &lrc, &lrc_size, &icon, &icon_size);
	if (ret < 0) {
		goto L2;
	}

	arg.fifo = fifo;
	arg.file = file;
	ret = pthread_create(&tid, NULL, load_to_fifo, &arg);
	if (ret < 0) {
		goto L2;
	}

	dec = decode_open(MPAUDEC); // fixme!

	// show_icon(icon, icon_size);

	mp3_size = fifo_read(fifo, mp3_buff, sizeof(mp3_buff));
	get_mp3_param(dec, mp3_buff, mp3_size, &mp3_pm);

	out = open_audio(AUDIO_ALSA, &mp3_pm);
	if (NULL == out) {
		ret = -ENODEV;
		goto L3;
	}

	size = mp3_size;
	while (size < file->size) {
		raw_size = sizeof(raw_buff);

		if (mp3_size > 0) {
			ret = decode(dec, raw_buff, &raw_size, mp3_buff, mp3_size);
			mp3_size -= ret;
		}

		play_frames(out, raw_buff, raw_size, &mp3_pm, lrc, lrc_size);

		ret = fifo_read(fifo, mp3_buff, sizeof(mp3_buff) - mp3_size);
		mp3_size += ret;
	}

	close_audio(out);
L3:
	decode_close(dec);
L2:
	fifo_close(fifo);
L1:
	sound_file_close(file);

	return ret;
}
