# nthash - Generate NT Hash

CC	:= gcc
CFLAGS	+= $(shell pkg-config --cflags --libs nettle)
VERSION	= $(shell git describe --tags --long)

all: nthash.c
	$(CC) $(CFLAGS) -o nthash nthash.c

clean:
	/bin/rm -f *.o *~ nthash
