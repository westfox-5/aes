#ifndef AES_H
#define AES_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int size;
  char* data;
} Block;

typedef struct {
  int num_cols;
  int num_rows;
  int size;
  Block* blocks;
} Key;

const Key* create_key_128(const char* key_data, size_t key_size);

void dump_key(FILE* stream, const Key* key);
void dump_block(FILE* stream, Block* block, int i, int j);

#endif //AES_H
