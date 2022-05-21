#pragma once
#include <stdint.h>
#include <stdio.h>

//* Square-and-multiply algorithm
uint64_t exponentAndMod(uint64_t num, uint64_t exponent, short binExponent[64],
                        short binExpNumberOfBits, uint64_t mod);
//* Encrypt *.txt already exists and write to different file
void encryptTxt(FILE *initialFile, FILE *encryptedFile, uint64_t e,
                short binE[64], short binENumberOfBits, uint64_t n);

//* Decrypt ciphertext from *.txt to different file
void decryptTxt(FILE *encryptedFile, FILE *decryptedFile, uint64_t d,
                short binD[64], short binDNumberOfBits, uint64_t n);
