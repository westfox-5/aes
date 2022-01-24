#include "key.h"

#include <string.h>

Key* create_key_128(const char* data, size_t size) {
#define KEY_MAX_SIZE 128
	
	if (size >= KEY_MAX_SIZE) {
		fprintf(stderr, "Error: Key size exceeded maximum length. Excepted key size of length %u bytes, but instead got %zu bytes.\n", KEY_MAX_SIZE, size);
		exit(1);
	}
	
	int num_blocks = KEY_MAX_SIZE / BLOCK_MAX_SIZE;
	int num_cols = KEY_MAX_SIZE / 32;
	int num_rows = num_blocks / num_cols;

	Key* key = (Key *) malloc(sizeof(Key));
	key->size = num_blocks;
	key->num_cols = num_cols;	
	key->num_rows = num_rows;
	key->blocks = (Block**) malloc(sizeof(Block*) * KEY_MAX_SIZE);
	
	int mapped_size = 0; // keep pointer to last byte mapped from input to key
	for (int col=0; col<num_cols; ++col) {
		for (int row=0; row<num_rows; ++row) {
			int idx = (col*num_rows) + row;
			
			// calculate if BLOCK_MAX_SIZE data is available in input
			int available_size = ((size - mapped_size) > BLOCK_MAX_SIZE) ? (BLOCK_MAX_SIZE) : (size - mapped_size);

			Block* block = (Block*) malloc(sizeof(Block));
			block->size = BLOCK_MAX_SIZE;
			block->data = (char*) malloc(sizeof(char) * BLOCK_MAX_SIZE);
			block->row = row;
			block->col = col;
			
			// TODO: eventually manipulate bytes [data+mapped_size ... data+mapped_size+available_size] before setting them in key
			
 			memcpy(block->data, data + mapped_size, available_size);
			memset(block->data + available_size, '\0', (BLOCK_MAX_SIZE-available_size)); // fill remaining bytes with 0s
			mapped_size += available_size; 
			
			key->blocks[idx] = block;
		}
	}
	
	return key;
}

void dispose_key(Key* key)
{
	for (int i=0; i<key->size; ++i) {
		dispose_block(key->blocks[i]);
	}
	free(key->blocks);
	key->size = 0;
}

void dump_key(FILE* stream, const Key* key)
{
	
	fprintf(stream, "----------- BEGIN KEY -----------\n");
	if (key->size > 0) {
		for (int r=0; r<key->num_rows; ++r) {
			for (int c=0; c<key->num_cols; ++c) {
				int idx = (c*key->num_rows) + r;
				dump_block(stream, key->blocks[idx]);
			}
			fprintf(stream, "\n");
		}
	}
	fprintf(stream, "----------- END KEY -------------\n");
}
