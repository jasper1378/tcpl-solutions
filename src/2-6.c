#include <stdio.h>

unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y) {
  return ((x & ~(~(~0 << n) << (p + 1 - n))) |
          ((y & (~(~0 << n))) << (p + 1 - n)));
}

int main() {
  unsigned x;
  unsigned p;
  unsigned n;
  unsigned y;

  scanf("%u", &x);
  scanf("%u", &p);
  scanf("%u", &n);
  scanf("%u", &y);
  printf("%u\n", setbits(x, p, n, y));

  return 0;
}
