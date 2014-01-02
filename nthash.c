/*
 * (C) 2012-2014 by Christian Hesse <mail@eworm.de>
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
#include <iconv.h>

#include <nettle/md4.h>

#define BUF_SIZE	64
#define TOCODE		"UTF-16LE"
#define FROMCODE	"UTF-8"

int main(int argc, char **argv) {
	struct md4_ctx ctx;
	char buffer[BUF_SIZE], buffernull[2 * BUF_SIZE];
	char *in = buffer, *out = buffernull;
	uint8_t digest[MD4_DIGEST_SIZE];
	int i, linebreak = 0;
	size_t done, inbytes, outbytes;
	iconv_t conv;

	md4_init(&ctx);
	while (1) {
		done = inbytes = fread(buffer, 1, BUF_SIZE, stdin);
		outbytes = 2 * inbytes;

		if (strstr(buffer, "\n") != NULL)
			linebreak++;

		conv = iconv_open(TOCODE, FROMCODE);
		iconv(conv, &in, &inbytes, &out, &outbytes);
		iconv_close(conv);

		md4_update(&ctx, done * 2 - outbytes, (unsigned char *)buffernull);
		if (done < BUF_SIZE)
			break;
	}
	if (ferror(stdin))
		return EXIT_FAILURE;

	if (linebreak)
		fprintf(stderr, "Warning: Input contains line break!\n");

	md4_digest(&ctx, MD4_DIGEST_SIZE, digest);

	for (i = 0; i < MD4_DIGEST_SIZE; i++)
		printf("%02x", digest[i]);
	putchar('\n');

	return EXIT_SUCCESS;
}
