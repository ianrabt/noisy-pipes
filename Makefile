CC = cc
CFLAGS = -std=gnu17 -g -O0 -pedantic -Wall

all: binary-symmetric visualize

binary-symmetric: channel-binary-symmetric.c
	$(CC) $(CFLAGS) channel-binary-symmetric.c -o channels/binary-symmetric

visualize: visualize.c
	$(CC) $(CFLAGS) visualize.c -o visualize

.PHONY: clean
clean:
	rm visualize channels/binary-symmetric
