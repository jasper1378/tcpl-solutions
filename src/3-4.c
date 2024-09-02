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

int main() {
  char s[MAXSTR];
  int n;

  scanf("%d", &n);
  itoa(n, s);
  puts(s);

  return 0;
}
