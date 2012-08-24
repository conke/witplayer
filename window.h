#pragma once

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include "mp3.h"

#define FB_DEV "/dev/fb0"
#define LEN_W(a)  ((a) * 8 / 10)
#define LSK_H(b)  ((b) * 9 * 4 / 10)

int show_wave(u8 *raw_data, size_t size, struct mp3_param *param);
int show_icon(u8 *icon, size_t size);
int show_progressbar(size_t current, size_t total);
int show_text(int x, int y, const char *text, int color);
