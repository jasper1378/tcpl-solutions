int bitcount(unsigned x) {
  int b;

  for (b = 0; x; x &= (x - 1), ++b)
    ;

  return b;
}
