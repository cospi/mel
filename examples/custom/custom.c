#include <stddef.h>

static void custom_error(const char *error);
static void *custom_alloc(size_t size);
static void custom_free(void *memory);

#define mel_error custom_error
#define mel_alloc custom_alloc
#define mel_free custom_free
#include <mel.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void custom_error(const char *error)
{
	fprintf(stderr, "[Error] %s\n", error);
}

static void *custom_alloc(size_t size)
{
	if ((rand() % 100) < 50) {
		return malloc(size);
	}

	return NULL;
}

static void custom_free(void *memory)
{
	free(memory);
}

int main(void)
{
	char *path;
	char *directory;

	srand(time(NULL));

	path = mel_get_path();
	if (path != NULL) {
		puts(path);
		mel_free(path);
	}

	directory = mel_get_directory();
	if (directory != NULL) {
		puts(directory);
		mel_free(directory);
	}

	return 0;
}
