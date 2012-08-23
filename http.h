#pragma once
#include "sound_file.h"

struct sound_file_info *http_file_open(const char *URL);
int http_file_close(struct sound_file_info *file);
int http_file_load(struct sound_file_info *file, u8 *buff, size_t size);
