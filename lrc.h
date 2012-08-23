#pragma once
#include "types.h"
#include "sys/time.h"

int show_lyric(u8 *lrc_buff, size_t size, struct timeval *total, struct timeval *curr);
