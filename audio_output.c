#include "audio_output.h"

struct audio_output *open_audio(audio_dev_t type, struct mp3_param *param)
{
	// fixme!
//	struct audio_output *out;
//
//	out = malloc(sizeof(*out));
//	if (NULL == out) {
//		return NULL;
//	}
//
//	out->type = type;
//
//	if (type == AUDIO_ALSA) {
//		out->outdev = open_alsa();
//	} else if (type == AUDIO_GSTREAMER) {
//		out->outdev = open_gstreamer();
//	}

	return 0;
}

int close_audio(struct audio_output *out)
{
	// fixme!
//	if (out->type == AUDIO_ALSA) {
//		...
//	} else ...

	return 0;
}

int play_frames(struct audio_output *out, u8 *raw_buff, size_t size, struct mp3_param *param, u8 *lrc, size_t lrc_size)
{
	// fixme!
//	if (out->type == AUDIO_ALSA) {
//		alsa_play_frames(out->outdev, raw_buff, size, param);
//	} else if (out->type == AUDIO_GSTREAMER) {
//		gstreamer_play_frames(out->outdev, raw_buff, size, param);
//	}

	return 0;
}
