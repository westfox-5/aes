#ifndef KEY_H
#define KEY_H

#include <stdio.h>
#include <stdlib.h>

#include "block.h"

typedef struct {
	int num_cols;
	int num_rows;
	int size;
	Block** blocks;
} Key;

Key* create_key_128(const char* data, size_t size);
void dispose_key(Key* key);

void dump_key(FILE* stream, const Key* key);


#endif //KEY_H
