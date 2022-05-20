#pragma once
#include <stdint.h>

//* Euler function for two primes numbers
uint64_t phi(uint64_t p, uint64_t q);

//* Extended Euclidean algorithm. Compute modular multiplicative inverse and gcd
//* r0 > r1
//* pTi is inverse to r1 by mod r0 <-- important
uint64_t eea(uint64_t r0, uint64_t r1, uint64_t *pTi);

//* Generates private and public keys
void keyGeneration(uint64_t *pPhiResult, uint64_t *pE, uint64_t *pD);