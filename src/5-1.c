#include <ctype.h>
#include <stdio.h>

#define getch() getchar()
#define ungetch(c_) ungetc((c_), stdin)

int getint(int *pn) {
  int c, sign;

  while (isspace(c = getch()))
    ;
  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c);
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-')
    c = getch();
  if (!isdigit(c) && c != EOF) {
    ungetch(c);
    return 0;
  }
  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');
  *pn *= sign;
  if (c != EOF)
    ungetch(c);
  return c;
}

int main() {
  int i;

  while (getint(&i) > 0) {
    printf("%d\n", i);
  }

  return 0;
}
