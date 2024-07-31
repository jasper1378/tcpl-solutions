void reverse(char *s);

void itoa(int n, char *s, int w) {
  int i;
  int sign;

  if ((sign = n) < 0) {
    n = -n;
  }
  i = 0;
  do {
    s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);
  if (sign < 0) {
    --w;
  }
  for (; i < w; ++i) {
    s[i] = '0';
  }
  if (sign < 0) {
    s[i++] = '-';
  }
  s[i] = '\0';
  reverse(s);
}
