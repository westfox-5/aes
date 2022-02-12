#include <assert.h>

#include "aes.h"

static int getRoundsCount(State *state, const Key *key) {
	assert(0 && "Not Implemented");
}

static void expandKey(const Key *key, Key *expandedKey) {
	assert(0 && "Not Implemented");	
}


static void addRoundKey(State *state, const Key *key) {
	assert(0 && "Not Implemented");
}

static void round(State *state, const Key *key, const int displacement) {
	assert(0 && "Not Implemented");
}

static void finalRound(State *state, const Key *key, const int displacement) {
	assert(0 && "Not Implemented");
}

void encrypt(State *state, const Key *key)
{
	int num_rounds = getRoundsCount(state, key);

	Key *expandedKey;
	expandKey(key, expandedKey);

	addRoundKey(state, expandedKey);
	for (int i=1; i<num_rounds; ++i) {
		round(state, expandedKey, expandedKey->block_size*i);
	}
	finalRound(state, expandedKey, expandedKey->block_size*num_rounds);
}
