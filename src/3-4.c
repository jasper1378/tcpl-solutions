void reverse(char *s);

void itoa(int n, char *s) {
  int i;
  int sign;

  sign = ((n < 0) ? -1 : 1);
  i = 0;
  do {
    s[i++] = (n % 10) * sign + '0';
  } while ((n /= 10) * sign > 0);
  if (sign < 0) {
    s[i++] = '-';
  }
  s[i] = '\0';
  reverse(s);
}
