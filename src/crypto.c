#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

uint64_t exponentAndMod(uint64_t num, uint64_t exponent, uint64_t mod) {
  uint64_t res = num;
  int i = 0;
  int bin[64];

  while (exponent > 0) {
    bin[i] = (exponent % 2) == 1;
    exponent /= 2;
    i++;
  }

  i--; //* /0/0 second bit from the left

  while (i > 0) {
    res = (res * res) % mod;
    if (1 == bin[--i]) {
      res = (res * num) % mod;
    };
  }
  return res;
}

void encryptTxt(FILE *initialFile, FILE *encryptedFile, uint64_t e,
                uint64_t n) {
  char c;
  uint64_t num;
  do {
    c = fgetc(initialFile);
    if (feof(initialFile)) {
      return;
    }
    num = exponentAndMod(c, e, n);
    fprintf(encryptedFile, " %llu", num);
  } while (1);
}

void decryptTxt(FILE *encryptedFile, FILE *decryptedFile, uint64_t d,
                uint64_t n) {
  uint64_t num;
  fseek(encryptedFile, 0, SEEK_SET);
  while (fscanf(encryptedFile, "%llu", &num) != EOF) {
    num = exponentAndMod(num, d, n);
    fprintf(decryptedFile, "%c", num);
  }
}
