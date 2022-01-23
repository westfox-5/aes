#include "aes.h"

#include <string.h>

const Key* create_key_128(const char* data, size_t size) {
#define KEY_MAX_SIZE 128
#define BLOCK_MAX_SIZE 8

	if (size >= KEY_MAX_SIZE) {
		fprintf(stderr, "Error: Key size exceeded maximum length. Excepted key size of length %u bytes, but instead got %zu bytes.\n", KEY_MAX_SIZE, size);
		exit(1);
	}

	Key *key = (Key *) malloc(sizeof(Key));
	
	int num_blocks = KEY_MAX_SIZE / BLOCK_MAX_SIZE;
	int num_cols = KEY_MAX_SIZE / 32;
	int num_rows = num_blocks / num_cols;	

	//	printf("blocks: %u\n", num_blocks);
	//  printf("cols: %u\n", num_cols);
	//	printf("rows: %u\n", num_rows);

	key->num_cols = num_cols;
	key->num_rows = num_rows;
	
	key->size = KEY_MAX_SIZE;
	key->blocks = (Block*) malloc(sizeof(Block) * KEY_MAX_SIZE);

	int mapped_size = 0; // keep pointer to last byte mapped from input to key
	for (int i=0; i<num_cols; ++i) {
		for (int j=0; j<num_rows; ++j) {
			int idx = (j*num_cols) + i;
			
			Block block = {0};
			
			// calculate if BLOCK_MAX_SIZE data is available in input
			int available_size = ((size - mapped_size) > BLOCK_MAX_SIZE) ? (BLOCK_MAX_SIZE) : (size - mapped_size);

			block.size = BLOCK_MAX_SIZE;
			block.data = (char*) malloc(sizeof(char) * BLOCK_MAX_SIZE);

			// eventually manipulate [data+mapped_size...data+mapped_size+available_size] before setting in key
			
 			memcpy(block.data, data + mapped_size, available_size);
			memset(block.data + available_size, '\0', (BLOCK_MAX_SIZE-available_size)); // fill remaining bytes with 0s

			mapped_size += available_size; 
			
			key->blocks[idx] = block;
		}
	}
	
	return key;
}


void dump_block(FILE* stream, Block* block, int i, int j)
{
  for (int i=0; i<block->size; ++i) {
	  fprintf(stream, "(%u,%u):%hhx",i,j, block->data[i]);
	  if (!block->data[i]) {
		  fprintf(stream, "\t");
	  }
  }
  fprintf(stream, "\t");
  
  
}

void dump_key(FILE* stream, const Key* key)
{
  for (int j=0; j<key->num_cols; ++j) {
	for (int i=0; i<key->num_rows; ++i) {
	  int idx = i*key->num_cols + j;
	  dump_block(stream, &key->blocks[idx], i/*row*/, j/*col*/);
	}
	fprintf(stream, "\n");
  }
}
