#include <math.h>
#include <stdio.h>

#define MAXSTR 100

int itob(int n, char *s, int b) {
  int sign;
  int power;
  int digit;
  int ch;

  sign = ((n < 0) ? -1 : 1);
  if (sign == -1) {
    *s++ = '-';
  }

  switch (b) {
  case 2: {
    *s++ = '0';
    *s++ = 'b';
  } break;
  case 8: {
    *s++ = '0';
  } break;
  case 10: {
  } break;
  case 16: {
    *s++ = '0';
    *s++ = 'x';
  } break;
  default: {
    *s = '\0';
    return -1;
  } break;
  }

  if (n == 0) {
    *s++ = '0';
  } else {
    power = (int)pow(b, (int)(log(sign * n) / log(b)));

    while (power > 0) {
      digit = (n * sign) / power;
      if (digit >= 10) {
        ch = 'a' + (digit - 10);
      } else {
        ch = '0' + digit;
      }
      *s++ = ch;
      n %= power;
      power /= b;
    }
  }

  *s = '\0';

  return 0;
}

int main() {
  int n;
  int b;
  char s[MAXSTR];

  scanf("%d", &n);
  scanf("%d", &b);
  itob(n, s, b);
  puts(s);

  return 0;
}
