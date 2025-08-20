#ifndef MEL_H_
#define MEL_H_

#ifdef __linux__

#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE 200112L
#endif

#include <unistd.h>
#include <linux/limits.h>

#include <stdio.h>
#include <stdlib.h>

static char *_mel_linux_get_path_and_length(ssize_t *out_length)
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

static ssize_t _mel_linux_get_directory_separator_index(const char *path, ssize_t length)
{
	for (ssize_t i = length - 1; i >= 0; --i) {
		if (path[i] == '/') {
			return i;
		}
	}

	return -1;
}

static char *mel_get_path(void)
{
	ssize_t length;
	return _mel_linux_get_path_and_length(&length);
}

static char *mel_get_directory(void)
{
	ssize_t length;
	char *directory = _mel_linux_get_path_and_length(&length);
	if (directory == NULL) {
		return NULL;
	}

	ssize_t separator_index = _mel_linux_get_directory_separator_index(directory, length);
	if (separator_index == -1) {
		fputs("Getting separator index failed.\n", stderr);
		free(directory);
		return NULL;
	}

	directory[separator_index + 1] = '\0';
	return directory;
}

#else

#include <stdio.h>

static void _mel_unsupported_platform(void)
{
	puts("Unsupported platform.");
}

static char *mel_get_path(void)
{
	_mel_unsupported_platform();
	return NULL;
}

static char *mel_get_directory(void)
{
	_mel_unsupported_platform();
	return NULL;
}

#endif

#endif // MEL_H_
