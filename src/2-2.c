for (i = 0; i < lim - 1; ++i) {
  c = getchar();
  if (c == '\n') {
    break;
  }
  if (c == EOF) {
    break;
  }
  s[i] = c;
}
