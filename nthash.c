/*
 * (C) 2012-2020 by Christian Hesse <mail@eworm.de>
 *
 * Base on an example from:
 * http://www.lysator.liu.se/~nisse/nettle/nettle.html#Example
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <langinfo.h>
#include <iconv.h>

#include <nettle/md4.h>

#define BUF_SIZE	64

int main(int argc, char **argv) {
	struct md4_ctx ctx;
	char inbuffer[BUF_SIZE], outbuffer[2 * BUF_SIZE];
	char *in = inbuffer, *out = outbuffer;
	uint8_t digest[MD4_DIGEST_SIZE];
	int i, linebreak = 0;
	size_t done, inbytes, outbytes;
	iconv_t conv;

	if (setlocale(LC_ALL, "") == NULL) {
		fprintf(stderr, "Failed to initialize locale\n");
		return EXIT_FAILURE;
	}

	md4_init(&ctx);

	while (1) {
		done = inbytes = fread(inbuffer, 1, sizeof(inbuffer), stdin);
		outbytes = sizeof(outbuffer);

		if (strstr(inbuffer, "\n") != NULL)
			linebreak++;

		conv = iconv_open("UTF-16LE", nl_langinfo(CODESET));
		if (iconv(conv, &in, &inbytes, &out, &outbytes) == -1) {
			fprintf(stderr, "Failed to convert characters\n");
			return EXIT_FAILURE;
		}
		iconv_close(conv);

		md4_update(&ctx, sizeof(outbuffer) - outbytes, (unsigned char *)outbuffer);
		if (done < sizeof(inbuffer))
			break;
	}

	if (linebreak)
		fprintf(stderr, "Warning: Input contains line break!\n");

	md4_digest(&ctx, MD4_DIGEST_SIZE, digest);

	for (i = 0; i < MD4_DIGEST_SIZE; i++)
		printf("%02x", digest[i]);
	putchar('\n');

	return EXIT_SUCCESS;
}
