#ifndef MEL_H_
#define MEL_H_

#ifdef __linux__
	// _POSIX_C_SOURCE is required by readlink.
	#ifndef _POSIX_C_SOURCE
		#define _POSIX_C_SOURCE 200112L
	#endif
#endif

#ifndef mel_error
	#include <stdio.h>
	#define mel_error(_mel_error) fputs(_mel_error "\n", stderr)
#endif

#ifndef mel_alloc
	#include <stdlib.h>
	#define mel_alloc malloc
#endif

#ifndef mel_free
	#include <stdlib.h>
	#define mel_free free
#endif

/* ----------------------------------------------------------------------------------------------------------------- */
#if defined(__linux__)
/* ----------------------------------------------------------------------------------------------------------------- */

#include <unistd.h>
#include <linux/limits.h>

#include <stdlib.h>

static char *_mel_linux_get_path_and_length(ssize_t *out_length)
{
	char *path;
	ssize_t length;

	// Cast to be compatible with C++.
	path = (char *)mel_alloc(PATH_MAX);
	if (path == NULL) {
		mel_error("Memory allocation failed.");
		return NULL;
	}

	length = readlink("/proc/self/exe", path, PATH_MAX- 1);
	if (length <= 0) {
		mel_error("readlink failed.");
		mel_free(path);
		return NULL;
	}

	path[length] = '\0';
	*out_length = length;
	return path;
}

static ssize_t _mel_linux_get_directory_separator_index(const char *path, ssize_t length)
{
	ssize_t i;

	for (i = length - 1; i >= 0; --i) {
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
	char *directory;
	ssize_t separator_index;

	directory = _mel_linux_get_path_and_length(&length);
	if (directory == NULL) {
		return NULL;
	}

	separator_index = _mel_linux_get_directory_separator_index(directory, length);
	if (separator_index == -1) {
		mel_error("Getting separator index failed.");
		mel_free(directory);
		return NULL;
	}

	directory[separator_index + 1] = '\0';
	return directory;
}

/* ----------------------------------------------------------------------------------------------------------------- */
#elif defined(_WIN32)
/* ----------------------------------------------------------------------------------------------------------------- */

#include <Windows.h>

static char *_mel_windows_get_path_and_length(size_t *out_length)
{
	char *path;
	DWORD length;
	size_t i;

	// Cast to be compatible with C++.
	path = (char *)mel_alloc(MAX_PATH);
	if (path == NULL) {
		mel_error("Memory allocation failed.");
		return NULL;
	}

	length = GetModuleFileNameA(NULL, path, MAX_PATH);
	if (length == 0) {
		mel_error("GetModuleFileNameA failed.");
		mel_free(path);
		return NULL;
	}

	for (i = 0; i < length; ++i) {
		if (path[i] == '\\') {
			path[i] = '/';
		}
	}

	path[length] = '\0';
	*out_length = length;
	return path;
}

static int _mel_windows_get_directory_separator_index(const char *path, size_t length)
{
	int i;

	for (i = (int)length - 1; i >= 0; --i) {
		char character = path[i];
		if (character == '/') {
			return i;
		}
	}

	return -1;
}

static char *mel_get_path(void)
{
	size_t length;
	return _mel_windows_get_path_and_length(&length);
}

static char *mel_get_directory(void)
{
	size_t length;
	char *directory;
	int separator_index;

	directory = _mel_windows_get_path_and_length(&length);
	if (directory == NULL) {
		return NULL;
	}

	separator_index = _mel_windows_get_directory_separator_index(directory, length);
	if (separator_index == -1) {
		mel_error("Getting separator index failed.");
		mel_free(directory);
		return NULL;
	}

	directory[separator_index + 1] = '\0';
	return directory;
}

/* ----------------------------------------------------------------------------------------------------------------- */
#else
/* ----------------------------------------------------------------------------------------------------------------- */

static void _mel_unsupported_platform(void)
{
	mel_error("Unsupported platform.");
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

/* ----------------------------------------------------------------------------------------------------------------- */
#endif
/* ----------------------------------------------------------------------------------------------------------------- */

#endif
