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

static ssize_t mel_get_separator_index(const char *path, ssize_t length)
{
	for (ssize_t i = length - 1; i >= 0; --i) {
		if (path[i] == '/') {
			return i;
		}
	}

	return -1;
}

static char *mel_directory(void)
{
	ssize_t length;
	char *directory = mel_path(&length);
	if (directory == NULL) {
		return NULL;
	}

	ssize_t separator_index = mel_get_separator_index(directory, length);
	if (separator_index == -1) {
		fputs("Getting separator index failed.\n", stderr);
		free(directory);
		return NULL;
	}

	directory[separator_index + 1] = '\0';
	return directory;
}

int main(void)
{
	ssize_t length;
	char *path = mel_path(&length);
	if (path != NULL) {
		puts(path);
		free(path);
	}

	char *directory = mel_directory();
	if (directory != NULL) {
		puts(directory);
		free(directory);
	}

	return EXIT_SUCCESS;
}
