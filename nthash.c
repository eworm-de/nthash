/*
 * (C) 2012-2016 by Christian Hesse <mail@eworm.de>
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 * Base on an example from:
 * http://www.lysator.liu.se/~nisse/nettle/nettle.html#Example
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
