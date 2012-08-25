#include "audio_output.h"
#include "alsa.h"
#include <stdlib.h>

struct audio_output *open_audio(audio_dev_t type, struct mp3_param *param) {
	struct audio_output *out;

	out = malloc(sizeof(*out));
	if (NULL == out) {
		return NULL;
	}

	out->type = type;

	switch (type) {
	case AUDIO_GSTREAMER:
		// out->outdev = open_gstreamer(param); fixme!
		break;

	case AUDIO_ALSA:
		out->outdev = open_alsa(param);
		if (NULL == out->outdev) {
			free(out);
			return NULL;
		}
		break;
	}

	return out;
}

int close_audio(struct audio_output *out) {
	switch (out->type) {
	case AUDIO_GSTREAMER:
		// close_gstreamer(out);
		break;

	case AUDIO_ALSA:
		close_alsa(out->outdev);
		break;
	}

	free(out);

	return 0;
}

int play_frames(struct audio_output *out, u8 *raw_buff, size_t size, struct mp3_param *param, u8 *lrc, size_t lrc_size)
{
	int frames;
	int ret;

	frames = size / (param->channels * param->bits_per_sample / 8);

	switch (out->type) {
	case AUDIO_GSTREAMER:
		// play_gstreamer_frames(out->outdev, raw_buff, frames); fixme!
		break;

	case AUDIO_ALSA:
		ret = play_alsa_frames(out->outdev, raw_buff, frames);
		break;
	}


	return ret;
}
