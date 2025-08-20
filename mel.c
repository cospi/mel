#include "mel.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *path = mel_get_path();
	if (path != NULL) {
		puts(path);
		free(path);
	}

	char *directory = mel_get_directory();
	if (directory != NULL) {
		puts(directory);
		free(directory);
	}

	return EXIT_SUCCESS;
}
