#include <stdio.h>

#define MAXLINE 80
#define HEX
/* #define OCT */

int is_nongraph(char);
int print_nongraph(char);

int is_nongraph(char c) {
  return (((0x0 <= c) && (c <= 0x08)) || ((0x0e <= c) && (c <= 0x1f)) ||
          (c == 0x7f));
}
int print_nongraph(char c) {
  return printf(
#if defined(HEX)
      "<0x%x>"
#elif defined(OCT)
      "<0%o>"
#endif
      ,
      c);
}

int main() {
  int line;
  char c;

  while ((c = getchar()) != EOF) {
    if ((line + 1) == MAXLINE) {
      puts("\\");
      line = 0;
    }
    if (is_nongraph(c)) {
      line = print_nongraph(c);
    } else {
      ++line;
      putchar(c);
    }
  }
  return 0;
}
