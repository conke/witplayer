#pragma once
#include <sys/time.h>
#include "mp3.h"

int show_wave(u8 *raw_data, size_t size, struct mp3_param *param);
int show_icon(u8 *icon, size_t size);
int show_progressbar(size_t current, size_t total);
int show_text(int x, int y, const char *text, int color);
