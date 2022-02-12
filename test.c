#include <stdio.h>
#include <string.h>

#include "aes.h"

int main(void) {
	const char *passphrase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	// key creation & dumping
	Key *key = create_key_128(passphrase, strlen(passphrase));
	dump_key(stdout, key);

	// state creation & dumping
	const char *message = "This Message is Really Secret!";
	State *state = create_state_192(message, strlen(message));
	dump_state(stdout, state);

	encrypt(state, key);
	
	dispose_key(key);
	dispose_state(state);
	return 0;
}
