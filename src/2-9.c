#include <stdio.h>

int bitcount(unsigned x) {
  int b;

  for (b = 0; x; x &= (x - 1), ++b)
    ;

  return b;
}

int main() {
  unsigned x;

  scanf("%u", &x);
  printf("%u\n", x);

  return 0;
}
