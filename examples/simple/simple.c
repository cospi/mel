#include "mel.h"

#include <stdio.h>

int main(void)
{
	char *path;
	char *directory;

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
