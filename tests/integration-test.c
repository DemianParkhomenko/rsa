#include "../src/crypto.h"
#include "../src/key-gen.h"
#include <assert.h>
#include <stdint.h>

const char *GREEN = "\033[0;32m";
const char *RESET = "\033[0m";

void makeTest(uint64_t p, uint64_t q, char x) {
  uint64_t n = p * q;
  uint64_t phiResult = phi(p, q);
  uint64_t e;
  uint64_t d;
  keyGeneration(&phiResult, &e, &d);
  assert(e < n);

  uint64_t dummy; //*don't reassign private key
  uint64_t gcdPhiResultAndE = eea(phiResult, e, &dummy);
  uint64_t modInverseResEAndD = e * d % phiResult;
  assert(1 == gcdPhiResultAndE);
  assert(1 == modInverseResEAndD);
  uint64_t encrypted = exponentAndMod((uint64_t)x, e, n);
  char decrypted = (char)exponentAndMod(encrypted, d, n);
  assert(x == decrypted);

  printf("\n%sTest with p: %d, q: %d is valid.%s\n", GREEN, p, q, RESET);

  printf("• p: %d\n"
         "• q: %d\n"
         "• n: %d\n"
         "• phiResult: %d\n"
         "• e: %d\n"
         "• gcd of phi(n) and e: %d\n"
         "• d: %d\n"
         "• Modular multiplicative inverse. e * d mod phi(n):%d\n",
         p, q, n, phiResult, e, gcdPhiResultAndE, d, modInverseResEAndD);
}

void integrationTests() {
  printf("\nRunning tests...\n");
  makeTest(3323, 3331, 'U');
  makeTest(2351, 2591, 'K');
  makeTest(1889, 1471, 'R');
  makeTest(2251, 1123, 'A');
  makeTest(7159, 7919, 'I');
  makeTest(7027, 6359, 'N');
  makeTest(7919, 2351, 'E');
  makeTest(3, 11,
           '\0'); //*  the binary value of the plaintext x must be less than n
  //* so use null character which has 0 binary representation in ASCII table for
  //* small p and q (p*q = n)
}