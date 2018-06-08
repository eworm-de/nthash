nthash
======

**Generate NT Hash**

The NT hash is used by Microsoft and others for authentication. This
program `nthash` converts the standard input to UTF16 (little endian)
and applies the MD4 hash algorithm. This resulting 32 byte string is
printed to standard out.

Requirements
------------

To compile and run `ntash` you need:

* [nettle](http://www.lysator.liu.se/~nisse/nettle/)
* [markdown](http://daringfireball.net/projects/markdown/) (HTML documentation)

Additionally it is expected to have `make` and `pkg-config` around to
successfully compile.

Some systems may require additional development packages for the libraries.
Look for `nettle-dev` or similar.

Build and install
-----------------

Building and installing is very easy. Just run:

> make

followed by:

> make install

This will place an executable at `/usr/bin/nthash`.

Usage
-----

Just feed `nthash` with the password on standard input. Please not that
`nthash` does not strip new lines from input. You may want to use `echo`
with option `-n`:

    $ echo -n test | nthash
    0cb6948805f797bf2a82807973b89537

### Upstream

URL:
[GitHub.com](https://github.com/eworm-de/nthash#nthash)

Mirror:
[eworm.de](https://git.eworm.de/cgit.cgi/nthash/)
[GitLab.com](https://gitlab.com/eworm-de/nthash#nthash)
