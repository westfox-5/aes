#include "aes_state.h"
#include "util.h"

#include <string.h>

State* create_state_192(const char *data, int size)
{
#define STATE_SIZE 192

	int num_rows = 4;
	int num_cols = STATE_SIZE / 32;
	int num_blocks = num_rows * num_cols;
	int block_size = STATE_SIZE / num_blocks;
	
	State *state = (State*) malloc(sizeof(State));
	state->num_cols = num_cols;
	state->num_rows = num_rows;
	state->size = num_blocks;
	state->block_size = block_size;
	state->blocks = (Block**) malloc(sizeof(Block*) * num_blocks);

	/*
	printf("\n%d\t NUM_COLS\n", num_cols);
	printf("%d\t NUM_ROWS\n", num_rows);
	printf("%d\t NUM_BLOCKS\n", num_blocks);
	printf("%d\t BLOCK_SIZE\n\n", block_size);
	*/
	
	int mapped_size = 0; // keep pointer to last byte mapped from input
	for (int col=0; col<num_cols; ++col) {
		for (int row=0; row<num_rows; ++row) {
			int idx = index_from_coord(row, col, state->num_rows);
			
			// calculate if block_size data is available in input
			int available_size = ((size - mapped_size) > block_size) ? (block_size) : (size - mapped_size);

			Block *block = (Block*) malloc(sizeof(Block));
			block->size = block_size;
			block->data = (char*) malloc(sizeof(char) * block_size);
			block->row = row;
			block->col = col;
			
			// TODO: eventually manipulate bytes [data+mapped_size ... data+mapped_size+available_size] before setting them in state
			
 			memcpy(block->data, data + mapped_size, available_size);
			memset(block->data + available_size, '\0', (block_size-available_size)); // fill remaining bytes with 0s
			mapped_size += available_size;
			
			state->blocks[idx] = block;
		}
	}

	return state;
}

void dispose_state(State* state)
{
	for (int i=0; i<state->size; ++i) {
		dispose_block(state->blocks[i]);
	}
	free(state->blocks);
	free(state);
}

void dump_state(FILE *stream, const State *state)
{
	if (state->size > 0) {
		fprintf(stream, "----------- BEGIN STATE [ %3d ] -----------\n", state->size * state->block_size);
		for (int r=0; r<state->num_rows; ++r) {
			for (int c=0; c<state->num_cols; ++c) {
				int idx = index_from_coord(r, c, state->num_rows);
				dump_block(stream, state->blocks[idx]);
			}
			fprintf(stream, "\n");
		}
		fprintf(stream, "----------- END STATE ---------------------\n");
	}
}
