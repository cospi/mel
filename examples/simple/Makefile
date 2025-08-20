.PHONY : all clean

OUT := simple
SRC := simple.c

CC := gcc
CFLAGS += -Wall -Wextra -Wpedantic -ansi -I../../

all : $(OUT)

clean :
	$(RM) $(OUT)

$(OUT) : $(SRC)
	$(CC) $< -o $@ $(CFLAGS)
