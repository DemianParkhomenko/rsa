#pragma once
#include <stdint.h>
#include <stdio.h>

uint64_t exponentAndMod(uint64_t x, uint64_t y, uint64_t mod);
void encryptTxt(FILE *initialFile, FILE *encryptedFile, uint64_t exponent,
                uint64_t mod);
void decryptTxt(FILE *encryptedFile, FILE *decryptedFile, uint64_t exponent,
                uint64_t mod);