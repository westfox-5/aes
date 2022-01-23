#include <stdio.h>
#include <string.h>

#include "aes.h"
  
int main() {
  const char *passphrase = "ABCD";
  const Key *key = create_key_128(passphrase, strlen(passphrase));
  printf("Key created! [Passphrase: \'%s\', Size: %d]\n", passphrase, key->size);

  dump_key(stdout, key);

  return 0;
} 
