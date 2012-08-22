#include <stdlib.h>
#include "sound_file.h"

struct sound_file_info *sound_file_open(const char *URL)
{
	struct sound_file_info *file;

	file = malloc(sizeof(*file));
	if (NULL == file)
		return NULL;

	// fixme!

	return file;
}

int sound_file_close(struct sound_file_info *file)
{
	free(file);

	return 0;
}

int sound_file_load(struct sound_file_info *file, u8 *buff, size_t size)
{
	// fixme!

	return 0;
}
