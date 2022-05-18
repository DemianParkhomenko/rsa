#include <math.h>
#include <stdint.h>
#include <stdio.h>

uint64_t smallValuesForE[] = {3, 17, 65537};

uint64_t phi(uint64_t p, uint64_t q) { return (p - 1) * (q - 1); }

//* Extended Euclidean algorithm. Copmute modular multiplicative inverse and gcd
//* pTi is inverse to r1 by mod r0 <-- important
uint64_t eea(uint64_t r0, uint64_t r1, uint64_t *pTi) {
  uint64_t t0 = 0, t1 = 1, i = 2, ri;
  do {
    ri = r0 % r1;
    *pTi = t0 - (r0 - ri) / r1 * t1;
    r0 = r1;
    r1 = ri;
    t0 = t1;
    t1 = *pTi;
    i++;
  } while (ri != 0);
  *pTi = t0;
  return r0;
}

//* Square-and-multiply algorithm
uint64_t exponentAndMod(uint64_t x, uint64_t y, uint64_t mod) {
  int res = 1;
  while (y > 0) {
    if (y & 1) {
      res = res * x % mod;
    }
    y = y >> 1;
    x = x * x % mod;
  }
  return res;
}

void keyGeneration(uint64_t *pPhiResult, uint64_t *pE, uint64_t *pD) {
  size_t size = sizeof smallValuesForE / sizeof smallValuesForE[0];
  for (int i = 0; i < size; i++) {
    uint64_t gcd = eea(*pPhiResult, smallValuesForE[i], pD);
    if (1 == gcd && smallValuesForE[i] < *pPhiResult &&
        *pD * smallValuesForE[i] % *pPhiResult == 1) {
      *pE = smallValuesForE[i];
      return;
    }
  }
}

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
  return 0;
}
