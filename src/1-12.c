#include <stdio.h>

int main() {
  int in;
  int ch;

  in = 1;

  while ((ch = getchar()) != EOF) {
    if (ch == ' ' || ch == '\t' || ch == '\n') {
      if (in) {
        in = 0;
        putchar('\n');
      }
    } else {
      in = 1;
      putchar(ch);
    }
  }
}
