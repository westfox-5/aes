#include "aes_key.h"
#include "util.h"

#include <string.h>

Key* create_key_128(const char *data, int size)
{
#define KEY_SIZE 128

	int num_rows = 4;
	int num_cols = KEY_SIZE / 32;
	int num_blocks = num_rows * num_cols;
	int block_size = KEY_SIZE / num_blocks;

	Key *key = (Key*) malloc(sizeof(Key));
	key->num_cols = num_cols;	
	key->num_rows = num_rows;
	key->size = num_blocks;
	key->block_size = block_size;
	key->blocks = (Block**) malloc(sizeof(Block*) * num_blocks);

	/*
	printf("\n%d\t NUM_COLS\n", num_cols);
	printf("%d\t NUM_ROWS\n", num_rows);
	printf("%d\t NUM_BLOCKS\n", num_blocks);
	printf("%d\t BLOCK_SIZE\n\n", block_size);
	*/
	
	int mapped_size = 0; // keep pointer to last byte mapped from input
	for (int col=0; col<num_cols; ++col) {
		for (int row=0; row<num_rows; ++row) {
			int idx = index_from_coord(row, col, key->num_rows);
			
			// calculate if block_size data is available in input
			int available_size = ((size - mapped_size) > block_size) ? (block_size) : (size - mapped_size);

			Block *block = (Block*) malloc(sizeof(Block));
			block->size = block_size;
			block->data = (char*) malloc(sizeof(char) * block_size);
			block->row = row;
			block->col = col;
			
			// TODO: eventually manipulate bytes [data+mapped_size ... data+mapped_size+available_size] before setting them in key
			
 			memcpy(block->data, data + mapped_size, available_size);
			memset(block->data + available_size, '\0', (block_size-available_size)); // fill remaining bytes with 0s
			mapped_size += available_size; 
			
			key->blocks[idx] = block;
		}
	}
	
	return key;
}

void dispose_key(Key *key)
{
	for (int i=0; i<key->size; ++i) {
		dispose_block(key->blocks[i]);
	}
	free(key->blocks);
	key->size = 0;
}

void dump_key(FILE *stream, const Key *key)
{
	if (key->size > 0) {
		fprintf(stream, "----------- BEGIN KEY [ %3d ] -----------\n", key->size * key->block_size);
	    for (int r=0; r<key->num_rows; ++r) {
			for (int c=0; c<key->num_cols; ++c) {
				int idx = index_from_coord(r, c, key->num_rows);
				dump_block(stream, key->blocks[idx]);
			}
			fprintf(stream, "\n");
		}
		fprintf(stream, "----------- END KEY ---------------------\n");
	}
}
