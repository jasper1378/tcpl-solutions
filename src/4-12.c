#include <stdio.h>

#define MAXSTR 100

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

int main() {
  int n;
  char s[MAXSTR];

  scanf("%d", &n);
  itoa(n, s);
  puts(s);

  return 0;
}
