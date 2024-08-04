char *itoa(int n, char s[]) {
  if (n < 0) {
    *s++ = '-';
    n = -n;
  }
  if (n / 10) {
    s = itoa(n / 10, s);
  }
  *s++ = n % 10 + '0';
  *s = '\0';
  return s;
}
