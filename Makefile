# nthash - Generate NT Hash

CC	:= gcc
ECHO	:= echo
GREP	:= grep
CFLAGS	+= -O2 -Wall -Werror
CFLAGS	+= $(shell pkg-config --cflags --libs nettle)
VERSION	= $(shell git describe --tags --long)

all: nthash.c
	$(CC) $(CFLAGS) -o nthash nthash.c

check:
	$(ECHO) -n "testing123" | ./nthash | \
		$(GREP) '^3e 67 8b 26 6d 1d 44 9e 53 1e 92 be c3 3b 6d 27$$'

clean:
	/bin/rm -f *.o *~ nthash
