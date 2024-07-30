unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y) {
  return ((x & ~(~(~0 << n) << (p + 1 - n))) |
          ((y & (~(~0 << n))) << (p + 1 - n)));
}
