#ifndef BLOCK_H
#define BLOCK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int row;
	int col;
	int size;
	char *data;
} Block;

extern void dispose_block(Block *block);
extern void dump_block(FILE *stream, Block *block);

#endif //BLOCK_H
