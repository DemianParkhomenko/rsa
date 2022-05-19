#include "crypto.h"
#include "key-gen.h"
#include <stdint.h>
#include <stdio.h>

const char *INITIAL_FILE_PATH = "./txt/initial.txt";
const char *ENCRYPTED_FILE_PATH = "./txt/encrypted.txt";
const char *DECRYPTED_FILE_PATH = "./txt/decrypted.txt";

int main() {
  uint64_t p = 3457, q = 3571;
  uint64_t n = p * q;
  uint64_t phiResult = phi(p, q);
  uint64_t e, d;
  keyGeneration(&phiResult, &e, &d);
  printf("n %d\n", n);
  printf("phiResult:%d\n", phiResult);
  printf("e:%d\n", e);
  printf("d:%d\n", d);
  uint64_t x = (uint64_t)'A';
  printf("x:%d\n", x);
  uint64_t encrypted = exponentAndMod(x, e, n);

  printf("encrypted: %d\n", encrypted);
  uint64_t decrypted = exponentAndMod(encrypted, d, n);
  printf("decrypted: %d\n", decrypted);
  printf("%c\n", (char)x);

  FILE *initalFile = fopen(INITIAL_FILE_PATH, "r");
  FILE *encryptedFile = fopen(ENCRYPTED_FILE_PATH, "w+");
  FILE *decryptedFile = fopen(DECRYPTED_FILE_PATH, "w");

  encryptTxt(initalFile, encryptedFile, e, n);
  decryptTxt(encryptedFile, decryptedFile, d, n);

  return 0;
}
