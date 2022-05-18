#include <math.h>
#include <stdint.h>
#include <stdio.h>

uint64_t phi(uint64_t *p, uint64_t *q) { return (*p - 1) * (*q - 1); }

uint64_t eea(uint64_t e, uint64_t *pMod, uint64_t *d, uint64_t *badVar) {
  if (e == 0) {
    *d = 0, *badVar = 1;
    return *pMod;
  }
  uint64_t d1, badVar1;
  uint64_t gcd = eea(*pMod % e, &e, &d1, &badVar1);
  *d = badVar1 - (*pMod / e) * d1;
  *badVar = d1;
  return gcd;
}

void keyGeneration(uint64_t *pPhiResult, uint64_t *pE, uint64_t *pD) {
  uint64_t unnecessaryVar; // TODO fix unnecessary computing
  uint64_t smallValuesForE[] = {3, 7, 11, 17, 65537};
  size_t size = sizeof smallValuesForE / sizeof smallValuesForE[0];
  for (int i = 0; i < size; i++) {
    uint64_t gcd = eea(smallValuesForE[i], pPhiResult, pD, &unnecessaryVar);
    if (1 == gcd && smallValuesForE[i] < *pPhiResult &&
        *pD * smallValuesForE[i] % *pPhiResult == 1) {
      *pE = smallValuesForE[i];
      printf("%d * %d + %d * %d = %d\n", unnecessaryVar, *pPhiResult, *pD,
             smallValuesForE[i], gcd);
      return;
    }
  }
}

int main() {
  uint64_t p = 3, q = 11;
  uint64_t n = p * q;
  uint64_t phiResult = phi(&p, &q);
  uint64_t e, d;
  keyGeneration(&phiResult, &e, &d);
  printf("n %d\n", n);
  printf("phiResult:%d\n", phiResult);
  printf("e:%d\n", e);
  printf("d:%d\n", d);
  uint64_t x = 4;
  printf("x:%d\n", x);
  uint64_t encrypted = (uint64_t)pow(x, e) % n;

  printf("encrypted: %d\n", encrypted);
  uint64_t decrypted = (uint64_t)pow(encrypted, d) % n;
  printf("decrypted: %d\n", decrypted);

  return 0;
}
