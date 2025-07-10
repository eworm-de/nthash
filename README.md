nthash
======

[![GitHub stars](https://img.shields.io/github/stars/eworm-de/nthash?logo=GitHub&style=flat&color=red)](https://github.com/eworm-de/nthash/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/eworm-de/nthash?logo=GitHub&style=flat&color=green)](https://github.com/eworm-de/nthash/network)
[![GitHub watchers](https://img.shields.io/github/watchers/eworm-de/nthash?logo=GitHub&style=flat&color=blue)](https://github.com/eworm-de/nthash/watchers)

**Generate NT Hash**

The NT hash is used by Microsoft and others for authentication. This
program `nthash` converts the standard input to UTF16 (little endian)
and applies the MD4 hash algorithm. This resulting 32 byte string is
printed to standard out.

Requirements
------------

To compile and run `ntash` you need:

* [nettle](https://www.lysator.liu.se/~nisse/nettle/)
* [markdown](https://daringfireball.net/projects/markdown/) (HTML documentation)

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

License and warranty
--------------------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
[GNU General Public License](COPYING.md) for more details.

### Upstream

URL:
[GitHub.com](https://github.com/eworm-de/nthash#nthash)

Mirror:
[eworm.de](https://git.eworm.de/cgit.cgi/nthash/)
[GitLab.com](https://gitlab.com/eworm-de/nthash#nthash)

---
[⬆️ Go back to top](#top)
