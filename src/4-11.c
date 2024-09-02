#include <ctype.h>
#include <stdio.h>

#define MAXSTR 100

#define getch() getchar()

#define NUMBER '0'

int getop(char s[]) {
  int i, c;
  static int lc = ' ';

  if ((s[0] = c = lc) == ' ' || c == '\t')
    while ((s[0] = c = getch()) == ' ' || c == '\t')
      ;
  s[1] = '\0';
  if (!isdigit(c) && c != '.')
    return c;
  i = 0;
  if (isdigit(c))
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.')
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  if (c != EOF)
    lc = c;
  return NUMBER;
}

int main() {
  char s[MAXSTR];
  int o;

  while ((o = getop(s)) != EOF && o != '\n') {
    if (o == NUMBER) {
      puts(s);
    } else {
      putchar(o);
      putchar('\n');
    }
  }

  return 0;
}
