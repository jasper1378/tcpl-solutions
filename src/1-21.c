#include <stdio.h>

#define TAB_SIZE 8

#define NEXT_TABSTOP(pos_) ((((pos_) / TAB_SIZE) * TAB_SIZE) + TAB_SIZE)

int main() {
  int i;
  int ch;
  int cnt;
  int pos;

  pos = 0;

  for (;;) {
    cnt = 0;
    while ((ch = getchar()) == ' ') {
      ++cnt;
    }
    for (i = pos, pos += cnt; (i + cnt) > NEXT_TABSTOP(i);
         cnt -= (NEXT_TABSTOP(i) - i), i = NEXT_TABSTOP(i)) {
      putchar('\t');
    }
    for (; cnt > 0; --cnt) {
      putchar(' ');
    }
    if (ch == EOF) {
      break;
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
