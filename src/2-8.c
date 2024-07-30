#include <limits.h>

unsigned rightrot(unsigned x, unsigned n) {
  unsigned s;

  s = sizeof(x) * CHAR_BIT;
  return ((x >> (n % s)) | (x << ((s - n) % s)));
}
