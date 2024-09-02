#include <stdio.h>

unsigned invert(unsigned x, unsigned p, unsigned n) {
  return ((x & ~(~(~0 << n) << (p + 1 - n))) |
          (~x & (~(~0 << n) << (p + 1 - n))));
}

int main() {
  unsigned x;
  unsigned p;
  unsigned n;

  scanf("%u", &x);
  scanf("%u", &p);
  scanf("%u", &n);
  printf("%u\n", invert(x, p, n));

  return 0;
}
