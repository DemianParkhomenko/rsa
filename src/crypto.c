#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <uchar.h>

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

void encryptTxt(char *initialFileName, char *encryptedFileName, uint64_t e,
                char binE[64], short binENumberOfBits, uint64_t n) {
  FILE *initialFile = fopen(initialFileName, "r");
  FILE *encryptedFile = fopen(encryptedFileName, "w");
  if (NULL == initialFile || NULL == encryptedFile) {
    printf("Can not open file for encrypting.\n");
    exit(1);
  }

  char32_t c;
  uint64_t num;
  while ((c = fgetc(initialFile)) != EOF) {
    num = exponentAndMod(c, e, binE, binENumberOfBits, n);
    fprintf(encryptedFile, " %lu", num);
  }
  fclose(initialFile);
  fclose(encryptedFile);
}

void decryptTxt(char *encryptedFileName, char *decryptedFileName, uint64_t d,
                char binD[64], short binDNumberOfBits, uint64_t n) {
  FILE *encryptedFile = fopen(encryptedFileName, "r");
  FILE *decryptedFile = fopen(decryptedFileName, "w");
  if (NULL == encryptedFile || NULL == decryptedFile) {
    printf("Can not open file for decrypting.\n");
    exit(1);
  }

  uint64_t num;
  while (fscanf(encryptedFile, "%lu", &num) != EOF) {
    num = exponentAndMod(num, d, binD, binDNumberOfBits, n);
    fprintf(decryptedFile, "%c", (char32_t)num); 
  }
  fclose(encryptedFile);
  fclose(decryptedFile);
}
