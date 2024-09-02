#include <stdio.h>

#define MAXSTR 100

int main() {
  char s[MAXSTR];
  int lim = MAXSTR;
  int i;
  int c;

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

  (void)s;

  return 0;
}
