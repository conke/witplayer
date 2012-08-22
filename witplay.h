#pragma once
#include <stdio.h>
#include "types.h"
#include "fifo.h"
#include "mp3.h"
#include "lrc.h"
#include "window.h"
#include "sound_file.h"

typedef enum {
	ALSA,
	GSTREAMER
} audio_dev_t;

struct audio_output *open_audio(audio_dev_t type, struct mp3_param *param);
int close_audio(struct audio_output *out);
size_t play_frames(struct audio_output *out, u8 *raw_buff, size_t size, struct mp3_param *param);
