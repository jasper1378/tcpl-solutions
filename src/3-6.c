#include <stdio.h>
#include <string.h>

#define MAXSTR 100

void reverse(char s[]) {
  int c, i, j;

  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

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

int main() {
  int n;
  int w;
  char s[MAXSTR];

  scanf("%d", &n);
  scanf("%d", &w);
  itoa(n, s, w);
  puts(s);

  return 0;
}
