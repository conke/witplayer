#pragma once
#include <stdio.h>
#include <pthread.h>
#include "types.h"

#define FIFO_LEN (1024 * 1024)

struct Fifo {
	u8 data[FIFO_LEN];
	size_t size;
	size_t read;
	size_t write;
	size_t used;
	pthread_mutex_t mutex;
};

size_t fifo_write(struct Fifo *fifo, u8 *buff, size_t size);
size_t fifo_read(struct Fifo *fifo, u8 *buff, size_t size);
