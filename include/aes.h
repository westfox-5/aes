#ifndef AES_HEADER
#define AES_HEADER

#include "aes_key.h"
#include "aes_state.h"

extern void encrypt(State *state, const Key *key);

#endif // AES_HEADER
