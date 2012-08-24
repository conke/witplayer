#include "window.h"

int show_wave(u8 *raw_data, size_t size, struct mp3_param *param)
{
	// fixme!

	return 0;
}

int show_icon(u8 *icon, size_t size)
{
	// fixme!

	return 0;
}

int show_progressbar(size_t current, size_t total)
{
	int i, j;
	int len = 0;
	int fd, ret;
	int width, hight;
	struct fb_fix_screeninfo fix;
	struct fb_var_screeninfo var;
	char blue[4] = {255, 0, 0, 0};
	char grean[4] = {0, 255, 0, 0};

	fd = open(FB_DEV, O_RDWR | O_NONBLOCK);
	if (fd < 0) {
		perror(FB_DEV);
		return -1;
	}

	ret = ioctl(fd, FBIOGET_VSCREENINFO, &var);
	if (ret < 0) {
		perror("FBIOGET_VSCREENINFO");
		close (fd);
		return -1;
	}

	ret = ioctl(fd, FBIOGET_FSCREENINFO, &fix);
	if (ret < 0) {
		perror("FBIOGET_FSCREENINFO");
		close (fd);
		return -1;
	}

	width = fix.line_length / ((var.bits_per_pixel + 7) / 8);
	hight = var.yres_virtual;

	len = current * LEN_W(width) / total ;
	lseek(fd, width * LSK_H(hight) + width / 4, SEEK_SET);
	for (i = 0; i < 10; i++) {
		for (j = 0; j < width; j++) {
			if ((j >= 0) && (j < len))
				write(fd, grean, 4);
			else if ((j >= len) && (j <= LEN_W(width)))
				write(fd, blue, 4);
			else
				lseek(fd, width * (LSK_H(hight) + 4 * i) + width / 4, SEEK_SET);
		}
	}

	close(fd);
	return 0;
}
