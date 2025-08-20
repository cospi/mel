.PHONY : all clean

OUT := custom
SRC := custom.c

CC := gcc
CFLAGS += -Wall -Wextra -Wpedantic -ansi -I../../

all : $(OUT)

clean :
	$(RM) $(OUT)

$(OUT) : $(SRC)
	$(CC) $< -o $@ $(CFLAGS)
