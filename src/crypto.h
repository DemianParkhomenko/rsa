#pragma once
#include <stdint.h>
#include <stdio.h>

//* Square-and-multiply algorithm
uint64_t exponentAndMod(uint64_t x, uint64_t y, uint64_t mod);

//* Encrypt *.txt already exists and write to different file
void encryptTxt(FILE *initialFile, FILE *encryptedFile, uint64_t exponent,
                uint64_t mod);

//* Decrypt ciphertext from *.txt to different file
void decryptTxt(FILE *encryptedFile, FILE *decryptedFile, uint64_t exponent,
                uint64_t mod);
