unsigned invert(unsigned x, unsigned p, unsigned n) {
  return ((x & ~(~(~0 << n) << (p + 1 - n))) |
          (~x & (~(~0 << n) << (p + 1 - n))));
}
