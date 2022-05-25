#include <stdint.h>
#include <stdio.h>

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

void encryptTxt(FILE *initialFile, FILE *encryptedFile, uint64_t e,
                char binE[64], short binENumberOfBits, uint64_t n) {
  char c;
  uint64_t num;
  do {
    c = fgetc(initialFile);
    if (feof(initialFile)) {
      return;
    }
    num = exponentAndMod(c, e, binE, binENumberOfBits, n);
    fprintf(encryptedFile, " %lu", num);
  } while (1);
}

void decryptTxt(FILE *encryptedFile, FILE *decryptedFile, uint64_t d,
                char binD[64], short binDNumberOfBits, uint64_t n) {
  uint64_t num;
  fseek(encryptedFile, 0, SEEK_SET);
  while (fscanf(encryptedFile, "%lu", &num) != EOF) {
    num = exponentAndMod(num, d, binD, binDNumberOfBits, n);
    fprintf(decryptedFile, "%c", (char)num); //* print char
  }
}
