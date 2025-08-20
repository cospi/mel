# mel

## Info

**mel** (**m**y **e**xecutable **l**ocation) is a single-header file ANSI C library that provides an absolute path to
the running executable and the directory it is located in.

Absolute paths are useful for opening files relative to the executable (rather than relative to the working directory).

**mel** currently supports Linux and Windows.

## Instructions

- Include `mel.h` in your project.
- Call `mel_get_path` to get the absolute path to the running executable.
- Call `mel_get_directory` to get the absolute path to the directory of the running executable.
- See the examples for reference.

## License

MIT, see the LICENSE file.

Copyright (c) 2025 Aleksanteri Hirvonen
