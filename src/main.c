#include "../tests/integration-test.h"
#include "crypto.h"
#include "key-gen.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

char *INITIAL_FILE_PATH = "./txt/initial.txt";
char *ENCRYPTED_FILE_PATH = "./txt/encrypted.txt";
char *DECRYPTED_FILE_PATH = "./txt/decrypted.txt";

#define runTest 1

int main() {
  if (runTest == 1) {
    integrationTests();
  }
  uint64_t p = 143669;
  uint64_t q = 29569;
  uint64_t n = p * q;
  uint64_t phiResult = phi(p, q);
  uint64_t e;
  uint64_t d;
  char binEArr[64];
  short binENumberOfBits;
  char binDArr[64];
  short binDNumberOfBits;
  keyGeneration(&phiResult, &e, &d, binEArr, &binENumberOfBits, binDArr,
                &binDNumberOfBits);

  printf("\nLogs from main:\n"
         "• p: %" PRIu64 "\n"
         "• q: %" PRIu64 "\n"
         "• n: %" PRIu64 "\n"
         "• phiResult: %" PRIu64 "\n"
         "• e: %" PRIu64 "\n"
         "• d: %" PRIu64 "\n",
         p, q, n, phiResult, e, d);

  encryptTxt(INITIAL_FILE_PATH, ENCRYPTED_FILE_PATH, e, binEArr,
             binENumberOfBits, n);
  decryptTxt(ENCRYPTED_FILE_PATH, DECRYPTED_FILE_PATH, d, binDArr,
             binDNumberOfBits, n);
  return 0;
}
