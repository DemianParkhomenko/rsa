#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t phi(uint64_t p, uint64_t q) { return (p - 1) * (q - 1); }

uint64_t eea(uint64_t r0, uint64_t r1, uint64_t *pD) {
  uint64_t t0 = 0, t1 = 1, i = 2, ri;
  do {
    ri = r0 % r1;
    *pD = t0 - (r0 - ri) / r1 * t1;
    r0 = r1;
    r1 = ri;
    t0 = t1;
    t1 = *pD;
    i++;
  } while (0 != ri);
  *pD = t0;
  return r0;
}

short fulfilBinArray(char bin[64], uint64_t num) {
  int i = 0;
  while (num) {
    bin[i] = (num & 1) + '0';
    num = num >> 1;
    i++;
  }
  return i;
}

void keyGeneration(uint64_t *pPhiResult, uint64_t *pE, uint64_t *pD,
                   char binEArr[64], short *binENumberOfBits, char binDArr[64],
                   short *binDNumberOfBits) {
  uint64_t smallValuesForE[] = {3, 5, 7, 11, 13, 17, 19, 257, 65537};
  size_t size = sizeof smallValuesForE / sizeof smallValuesForE[0];
  for (int i = 0; i < size; i++) {
    int gcd = eea(*pPhiResult, smallValuesForE[i],
                  pD); //* private key creates and assigns in eea
    if (1 == gcd && smallValuesForE[i] < *pPhiResult &&
        *pD * smallValuesForE[i] % *pPhiResult == 1 &&
        smallValuesForE[i] != *pD) {

      *pE = smallValuesForE[i];

      *binENumberOfBits = fulfilBinArray(binEArr, smallValuesForE[i]);
      *binDNumberOfBits = fulfilBinArray(binDArr, *pD);

      return; //* successful key generating
    }
  }
  printf("Error: can not generate keys. With phiResult: %lu\n", *pPhiResult);
  exit(1);
}