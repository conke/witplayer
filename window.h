#pragma once

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include "mp3.h"

typedef int color_t;

struct window {
	int x, y;
	int w, h;
};

struct progressbar_win {
	struct window win;
	color_t bar_color;
	color_t back_color;
	size_t max;
	size_t min;
	size_t cur;
};

struct text_win {
	struct window win;
	color_t font_color;
	color_t back_color;
	int font_size;
	char *text;
};

#define FB_DEV "/dev/fb0"
#define LEN_W(a)  ((a) * 8 / 10)
#define LSK_H(b)  ((b) * 9 * 4 / 10)

void *get_vm();
struct fb_fix_screeninfo *get_fix();
struct fb_var_screeninfo *get_var();

int show_wave(struct window *win, u8 *raw_data, size_t size, struct mp3_param *param);
int show_icon(struct window *win, u8 *icon, size_t size);
int show_progressbar(struct progressbar_win *bar);
int show_text(struct text_win *text);
