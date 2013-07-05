/*
 * (C) 2012-2013 by Christian Hesse <mail@eworm.de>
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 * Base on an example from:
 * http://www.lysator.liu.se/~nisse/nettle/nettle.html#Example
 */

#include <stdio.h>
#include <stdlib.h>
		 
#include <nettle/md4.h>
		 
#define BUF_SIZE 1024

int main(int argc, char **argv) {
	struct md4_ctx ctx;
	uint8_t buffer[BUF_SIZE], buffernull[2*BUF_SIZE];
	uint8_t digest[MD4_DIGEST_SIZE];
	int i, done;
	
	md4_init(&ctx);
	while (1) {
		done = fread(buffer, 1, sizeof(buffer), stdin);
		/* add null bytes to string */
		for (i = 0; i < done; i++) {
			if (buffer[i] == 0xa)
				fprintf(stderr, "Warning: Password contains line break!\n");
			else if (buffer[i] < 0x20 || buffer[i] == 0x7f)
				fprintf(stderr, "Warning: Password contains non-printable control character 0x%x!\n", buffer[i]);
			else if (buffer[i] > 0x7f)
				fprintf(stderr, "Warning: Password contains non-ASCII character 0x%x!\n", buffer[i]);
			buffernull[i*2] = buffer[i];
			buffernull[i*2+1] = 0;
		}
		md4_update(&ctx, done*2, buffernull);
		if (done < sizeof(buffer))
			break;
	}
	if (ferror(stdin))
		return EXIT_FAILURE;

	md4_digest(&ctx, MD4_DIGEST_SIZE, digest);

	for (i = 0; i < MD4_DIGEST_SIZE; i++)
		printf("%02x ", digest[i]);
	putchar('\n');

	return EXIT_SUCCESS;
}
