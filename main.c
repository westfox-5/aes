#include <stdio.h>
#include <string.h>

#include "aes.h"

int main() {
	const char *passphrase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	// test key creation & dumping
	Key* key = create_key_128(passphrase, strlen(passphrase));
	dump_key(stdout, key);

	// test key disposing & dumping (should fail)
	dispose_key(key);
	dump_key(stdout, key);

	return 0;
} 
