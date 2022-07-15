#include <inttypes.h>

#pragma once

struct Key {
  uint64_t key;
  char binKey[64];
  short binKeyNumberOfBits;
};
