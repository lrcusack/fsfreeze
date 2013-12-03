CC=gcc
CFLAGS= -g -Wall

all:
	make helper
	
helper: helper.h helper.c
	$(CC) $(CFLAGS) helper.c -o helper
	
clean:
	rm helper
