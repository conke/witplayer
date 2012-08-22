#pragma once
#include <stdio.h>
#include <pthread.h>
#include "types.h"

#define fifo_LEN (1024 * 1024)

struct fifo {
	u8 data[fifo_LEN];
	size_t size;
	size_t read;
	size_t write;
	size_t used;
	pthread_mutex_t mutex;
};

struct fifo *fifo_open();
int fifo_close(struct fifo *fifo);
int fifo_write(struct fifo *fifo, u8 *buff, size_t size);
int fifo_read(struct fifo *fifo, u8 *buff, size_t size);
