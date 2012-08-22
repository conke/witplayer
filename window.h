#pragma once
#include <sys/time.h>
#include "mp3.h"

int show_wave(u8 *raw_data, size_t size, struct mp3_param *param);
int show_lyric(u8 *lrc_buff, size_t size, struct timeval *total, struct timeval *curr);
int show_icon(u8 *icon, size_t size);
int show_progressbar(size_t current, size_t total);
