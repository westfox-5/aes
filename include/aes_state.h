#ifndef STATE_H
#define STATE_H

#include <stdio.h>
#include <stdlib.h>

#include "aes_block.h"

typedef struct {
	int num_cols;
	int num_rows;
	int size;
	int block_size;
	Block **blocks;
} State;

extern State* create_state_192(const char *data, int size);
extern void dump_state(FILE *stream, const State *state);
extern void dispose_state(State *state);

#endif //STATE_H
