#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE 200112L
#endif

#include <unistd.h>
#include <linux/limits.h>

#include <stdio.h>
#include <stdlib.h>


static char *mel_path(ssize_t *out_length)
{
	char *path = malloc(PATH_MAX);
	if (path == NULL) {
		fputs("malloc failed.\n", stderr);
		return NULL;
	}

	ssize_t length = readlink("/proc/self/exe", path, PATH_MAX- 1);
	if (length <= 0) {
		fputs("readlink failed.\n", stderr);
		free(path);
		return NULL;
	}

	path[length] = '\0';
	*out_length = length;
	return path;
}

int main(void)
{
	ssize_t length;
	char *path = mel_path(&length);
	if (path == NULL) {
		return EXIT_FAILURE;
	}

	puts(path);

	free(path);
	return EXIT_SUCCESS;
}
