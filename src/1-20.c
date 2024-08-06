#include <stdio.h>

#define TAB_SIZE 8

#define NEXT_TABSTOP(pos_) ((((pos_) / TAB_SIZE) * TAB_SIZE) + TAB_SIZE)

int main() {
  int ch;
  int pos;
  int tab;
  int i;

  pos = 0;

  while ((ch = getchar()) != EOF) {
    if (ch == '\t') {
      putchar(' ');
      ++pos;
      tab = NEXT_TABSTOP(pos);
      for (i = pos; i < tab; ++i) {
        putchar(' ');
        ++pos;
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
