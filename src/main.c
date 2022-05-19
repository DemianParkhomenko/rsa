#include "../tests/integration-test.h"
#include "crypto.h"
#include "key-gen.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#define __STDC_FORMAT_MACROS 1
#include <inttypes.h>

const char *INITIAL_FILE_PATH = "./txt/initial.txt";
const char *ENCRYPTED_FILE_PATH = "./txt/encrypted.txt";
const char *DECRYPTED_FILE_PATH = "./txt/decrypted.txt";

#define test 1

int main() {
  if (test == 1) {
    integrationTests();
  }
  uint64_t p = 131071;
  uint64_t q = 8191;
  uint64_t n = p * q;
  uint64_t phiResult = phi(p, q);
  uint64_t e;
  uint64_t d;
  keyGeneration(&phiResult, &e, &d);

  printf("\nLogs from main\n"
         "p: %" PRIu64 "\n"
         "q: %" PRIu64 "\n"
         "n: %" PRIu64 "\n"
         "phiResult: %" PRIu64 "\n"
         "e: %" PRIu64 "\n"
         "d: %" PRIu64 "\n",
         p, q, n, phiResult, e, d);

  FILE *initalFile = fopen(INITIAL_FILE_PATH, "r");
  FILE *encryptedFile = fopen(ENCRYPTED_FILE_PATH, "w+");
  FILE *decryptedFile = fopen(DECRYPTED_FILE_PATH, "w");
  assert(initalFile != NULL && encryptedFile != NULL && decryptedFile != NULL);

  encryptTxt(initalFile, encryptedFile, e, n);
  decryptTxt(encryptedFile, decryptedFile, d, n);

  fclose(initalFile);
  fclose(encryptedFile);
  fclose(decryptedFile);
  return 0;
}
