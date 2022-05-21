#pragma once
#include <stdint.h>

//* Euler function for two primes numbers
uint64_t phi(uint64_t p, uint64_t q);

//* Extended Euclidean algorithm. Compute modular multiplicative inverse and gcd
//* phiResult > e
//* pD is inverse to e by mod phiResult <-- important
uint64_t eea(uint64_t phiResult, uint64_t e, uint64_t *pD);

//* Generates private and public keys
void keyGeneration(uint64_t *pPhiResult, uint64_t *pE, uint64_t *pD,
                   short binEArr[64], short *binENumberOfBits,
                   short binDArr[64], short *binDNumberOfBits);