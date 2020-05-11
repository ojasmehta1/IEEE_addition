CC = gcc
CFLAGS	= -std=c99 -o -Werror -Wextra -Wall

all:
	$(CC) $(CFLAGS) assign2.c -o assign2
	./assign2 < input.txt > output.txt

clean:
	rm assign2 output.txt
