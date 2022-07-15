#include "./types/keys.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <uchar.h>

// todo research Chinese reminder theorem
uint64_t exponentAndMod(uint64_t num, uint64_t exponent, char binExponent[64],
                        short binExpNumberOfBits, uint64_t mod) {
  uint64_t res = num;
  binExpNumberOfBits--; //* /0/0 second bit from left

  while (binExpNumberOfBits > 0) {
    res = (res * res) % mod;
    if ('1' == binExponent[--binExpNumberOfBits]) {
      res = (res * num) % mod;
    };
  }
  return res;
}

void checkNullFilePointer(FILE *file, char *fileName) {
  if (NULL == file) {
    printf("Can not open file: %s.\n", fileName);
    exit(1);
  }
}

void encryptTxt(char *initialFileName, char *encryptedFileName,
                struct Key *public, uint64_t n) {
  FILE *initialFile = fopen(initialFileName, "r");
  FILE *encryptedFile = fopen(encryptedFileName, "w");
  checkNullFilePointer(initialFile, initialFileName);
  checkNullFilePointer(encryptedFile, encryptedFileName);

  char32_t c;
  uint64_t num;
  while ((c = fgetc(initialFile)) != EOF) {
    num = exponentAndMod((uint64_t)c, public->key, public->binKey,
                         public->binKeyNumberOfBits, n);
    fprintf(encryptedFile, " %lu", num);
  }
  fclose(initialFile);
  fclose(encryptedFile);
}

void decryptTxt(char *encryptedFileName, char *decryptedFileName,
                struct Key *private, uint64_t n) {
  FILE *encryptedFile = fopen(encryptedFileName, "r");
  FILE *decryptedFile = fopen(decryptedFileName, "w");
  checkNullFilePointer(encryptedFile, encryptedFileName);
  checkNullFilePointer(decryptedFile, decryptedFileName);

  uint64_t num;
  while (fscanf(encryptedFile, "%lu", &num) != EOF) {
    num = exponentAndMod(num, private->key, private->binKey,
                         private->binKeyNumberOfBits, n);
    fprintf(decryptedFile, "%c", (char32_t)num);
  }
  fclose(encryptedFile);
  fclose(decryptedFile);
}