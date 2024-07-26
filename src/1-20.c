#include <stdio.h>

#define TAB_SIZE 8

int main() {
  int ch;
  int pos;
  int i;

  pos = 0;

  while ((ch = getchar()) != EOF) {
    if (ch == '\t') {
      putchar(' ');
      ++pos;
      for (i = pos; (i % TAB_SIZE) != 0; ++i) {
        putchar(' ');
      }
    } else {
      putchar(ch);
      if (ch == '\n') {
        pos = 0;
      } else {
        ++pos;
      }
    }
  }
}
