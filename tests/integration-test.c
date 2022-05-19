#include "../src/crypto.h"
#include "../src/key-gen.h"
#include <assert.h>
#include <stdint.h>

const char *GREEN = "\033[0;32m";
const char *RED = "\033[0;31m";
const char *RESET = "\033[0m";

void makeTest(uint64_t p, uint64_t q, char x) {
  uint64_t n = p * q;
  uint64_t phiResult = phi(p, q);
  uint64_t e;
  uint64_t d;
  keyGeneration(&phiResult, &e, &d);
  uint64_t encrypted = exponentAndMod((uint64_t)x, e, n);
  char decrypted = (char)exponentAndMod(encrypted, d, n);
  if (p < 21 && q < 21) {
    printf("\nProof with small numbers\n"
           "p: %%d\n"
           "q: %%d\n"
           "n: %%d\n"
           "phiResult: %%d\n"
           "e: %%d\n"
           "d: %%d\n",
           p, q, n, phiResult, e, d);
  }
  if (x == decrypted) {
    printf("%sTest with p: %d, q: %d is valid.%s\n", GREEN, p, q, RESET);
  } else {
    printf("%sEXCEPTION: Test with p: %d, q: %d is NOT valid.%s\n", RED, p,
           RESET, q);
  }
}

void integrationTests() {
  makeTest(3323, 3331, 'U');
  makeTest(2351, 2591, 'K');
  makeTest(1889, 1471, 'R');
  makeTest(2251, 1123, 'A');
  makeTest(7159, 7919, 'I');
  makeTest(7027, 6359, 'N');
  makeTest(7919, 2351, 'E');
}