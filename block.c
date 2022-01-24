#include "block.h"

void dispose_block(Block* block)
{
	free(block->data);
	block->size = 0;
}

void dump_block(FILE* stream, Block* block)
{
	if (block->size <= 0) return;
	
	for (int i=0; i<block->size; ++i) {
		fprintf(stream, "%3x", block->data[i]);
	}
	fprintf(stream, "\t");
}
