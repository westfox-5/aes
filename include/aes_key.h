#ifndef KEY_H
#define KEY_H

#include <stdio.h>

#include "aes_block.h"

typedef struct {
	int num_cols;
	int num_rows;
	int size;
	int block_size;
	Block **blocks;
} Key;

extern Key* create_key_128(const char *data, int size);
extern void dispose_key(Key *key);
extern void dump_key(FILE *stream, const Key *key);

#endif //KEY_H
