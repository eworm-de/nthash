# nthash - Generate NT Hash
PREFIX  := /usr
CC	:= gcc
ECHO	:= echo
GREP	:= grep
INSTALL	:= install
RM	:= rm
CFLAGS	+= -O2 -Wall -Werror
# Debian has the libs but no pkg-config file. Fall back to hard coded
# "-lnettle" if pkg-config fails.
CFLAGS	+= $(shell pkg-config --cflags --libs nettle 2>/dev/null || echo "-lnettle")

all: nthash

nthash:
	$(CC) $(CFLAGS) -o nthash $(LDFLAGS) nthash.c

check:
	$(ECHO) -n "testing123" | ./nthash | \
		$(GREP) -q '^3e678b266d1d449e531e92bec33b6d27$$'
	$(ECHO) "testing123" | ./nthash 2>&1 | \
		$(GREP) -q '^Warning: Input contains line break!$$'

install: nthash
	$(INSTALL) -pDm0755 nthash $(DESTDIR)$(PREFIX)/bin/nthash

clean:
	$(RM) -f *.o *~ nthash
