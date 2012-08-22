#pragma once
#include "sound_file.h"

struct local_file_info *sound_file_open(const char *URL);
int local_file_close(struct sound_file_into *file);
size_t local_file_load(struct sound_file_into *file, u8 *buff, size_t size);
