#ifndef STATE_H
#define STATE_H

#include <stdio.h>
#include <stdlib.h>

#include "block.h"

typedef struct {
	int num_cols;
	int num_rows;
	int size;
	Block* blocks;
} State;

State* init_state(const char* data, size_t size);
void dispose_state(State* state);

#endif //STATE_H
