# nthash - Generate NT Hash

PREFIX	:= /usr
CC	:= gcc
MD	:= markdown
ECHO	:= echo
GREP	:= grep
INSTALL	:= install
RM	:= rm
CFLAGS	+= -O2 -Wall -Werror
# Debian has the libs but no pkg-config file. Fall back to hard coded
# "-lnettle" if pkg-config fails.
CFLAGS	+= $(shell pkg-config --cflags --libs nettle 2>/dev/null || echo "-lnettle")
VERSION	:= 0.1.4

all: nthash README.html

nthash: nthash.c
	$(CC) $(CFLAGS) -o nthash $(LDFLAGS) nthash.c

README.html: README.md
	$(MD) README.md > README.html

check:
	$(ECHO) -n "testing123" | ./nthash | \
		$(GREP) -q '^3e678b266d1d449e531e92bec33b6d27$$'
	$(ECHO) "testing123" | ./nthash 2>&1 | \
		$(GREP) -q '^Warning: Input contains line break!$$'

install: install-bin install-doc

install-bin: nthash
	$(INSTALL) -pD -m0755 nthash $(DESTDIR)$(PREFIX)/bin/nthash

install-doc: README.html
	$(INSTALL) -pD -m0644 README.md $(DESTDIR)$(PREFIX)/share/doc/nthash/README.md
	$(INSTALL) -pD -m0644 README.html $(DESTDIR)$(PREFIX)/share/doc/nthash/README.html

clean:
	$(RM) -f *.o *~ README.html nthash

release:
	git archive --format=tar.xz --prefix=nthash-$(VERSION)/ $(VERSION) > nthash-$(VERSION).tar.xz
	gpg -ab nthash-$(VERSION).tar.xz
