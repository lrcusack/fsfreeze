CC=gcc
CFLAGS= -g -Wall

all:
	make restore

restore: restore.h restore.c
	$(CC) $(CFLAGS) restore.c -o restore

clean:
	rm restore
