# nthash - Generate NT Hash

PREFIX	:= /usr

# commands
CC	:= gcc
MD	:= markdown
ECHO	:= echo
GREP	:= grep
INSTALL	:= install
RM	:= rm

# flags
CFLAGS	+= -std=c11 -O2 -fPIC -Wall -Werror
# Debian has the libs but no pkg-config file. Fall back to hard coded
# "-lnettle" if pkg-config fails.
CFLAGS	+= $(shell pkg-config --cflags --libs nettle 2>/dev/null || echo "-lnettle")
LDFLAGS	+= -Wl,-z,now -Wl,-z,relro -pie

# this is just a fallback in case you do not use git but downloaded
# a release tarball...
VERSION	:= 0.1.7

all: nthash README.html

nthash: nthash.c
	$(CC) nthash.c $(CFLAGS) $(LDFLAGS) -o nthash

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
	gpg --armor --detach-sign --comment nthash-$(VERSION).tar.xz nthash-$(VERSION).tar.xz
	git notes --ref=refs/notes/signatures/tar add -C $$(git archive --format=tar --prefix=nthash-$(VERSION)/ $(VERSION) | gpg --armor --detach-sign --comment nthash-$(VERSION).tar | git hash-object -w --stdin) $(VERSION)
