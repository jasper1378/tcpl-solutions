#include <limits.h>
#include <stdio.h>

unsigned rightrot(unsigned x, unsigned n) {
  unsigned s;

  s = sizeof(x) * CHAR_BIT;
  return ((x >> (n % s)) | (x << ((s - n) % s)));
}

int main() {
  unsigned x;
  unsigned n;

  scanf("%u", &x);
  scanf("%u", &n);
  printf("%u\n", rightrot(x, n));

  return 0;
}
