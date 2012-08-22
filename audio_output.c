#include "audio_output.h"

struct audio_output *open_audio(audio_dev_t type, struct mp3_param *param)
{
	// fixme!

	return 0;
}

int close_audio(struct audio_output *out)
{
	// fixme!

	return 0;
}

int play_frames(struct audio_output *out, u8 *raw_buff, size_t size, struct mp3_param *param, u8 *lrc, size_t lrc_size)
{
	// fixme!

	return 0;
}
