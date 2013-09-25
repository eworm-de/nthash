# nthash - Generate NT Hash

CC	:= gcc
ECHO	:= echo
GREP	:= grep
INSTALL	:= install
RM	:= rm
CFLAGS	+= -O2 -Wall -Werror
CFLAGS	+= $(shell pkg-config --cflags --libs nettle)

all: nthash

nthash:
	$(CC) $(CFLAGS) -o nthash nthash.c

check:
	$(ECHO) -n "testing123" | ./nthash | \
		$(GREP) -q '^3e678b266d1d449e531e92bec33b6d27$$'
	$(ECHO) "testing123" | ./nthash 2>&1 | \
		$(GREP) -q '^Warning: Input contains line break!$$'

install: nthash
	$(INSTALL) -D -m0755 nthash $(DESTDIR)/usr/bin/nthash

clean:
	$(RM) -f *.o *~ nthash
