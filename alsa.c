#include <alsa/asoundlib.h>
#include "audio_output.h"

#define DEVICE "hw:0,0"

void *open_alsa(struct mp3_param *param)
{
	int ret;
	snd_pcm_t *pcm;
	snd_pcm_hw_params_t *hwparams;

	ret = snd_pcm_open(&pcm, DEVICE, SND_PCM_STREAM_PLAYBACK, 0);
	if (ret < 0) {
		perror("snd_pcm_open");
		return NULL;
	}

	snd_pcm_hw_params_alloca(&hwparams);

	ret = snd_pcm_hw_params_any(pcm, hwparams);
	if (ret < 0) {
		perror("snd_pcm_hw_params_any");
		goto L1;
	}

	ret = snd_pcm_hw_params_set_access(pcm, hwparams, SND_PCM_ACCESS_RW_INTERLEAVED);
	if (ret < 0) {
		perror("snd_pcm_hw_params_set_sccess");
		goto L1;
	}

	ret = snd_pcm_hw_params_set_format(pcm, hwparams, SND_PCM_FORMAT_S16_LE);
	if (ret < 0) {
		perror("snd_pcm_hw_params_set_format");
		goto L1;
	}

	ret = snd_pcm_hw_params_set_channels(pcm, hwparams, param->channels);
	if (ret < 0) {
		perror("snd_pcm_hw_params_set_channels");
		goto L1;
	}

	ret = snd_pcm_hw_params_set_rate_near(pcm, hwparams, (unsigned int *)&param->rate, NULL);
	if (ret < 0) {
		perror("snd_pcm_hw_params_set_rate_near");
		goto L1;
	}

	ret = snd_pcm_hw_params(pcm, hwparams);
	if (ret < 0) {
		perror("snd_pcm_hw_params");
		goto L1;
	}

	ret = snd_pcm_prepare(pcm);
	if (ret < 0) {
		perror("snd_pcm_prepare");
		goto L1;
	}

	return pcm;

L1:
	snd_pcm_close(pcm);

	return NULL;
}

int close_alsa(snd_pcm_t *pcm)
{
	snd_pcm_close(pcm);

	return 0;
}

int play_alsa_frames(snd_pcm_t *pcm, u8 *raw_buff, int frames)
{

	snd_pcm_mmap_writei(pcm, raw_buff, frames);

	snd_pcm_drain(pcm);

	return 0;
}
