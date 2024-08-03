#include <ctype.h>
#include <stdio.h>

#define NUMBER '0'

int getch(void);
void ungetch(int);

int getop(char s[]) {
  int i, c;
  static int lc = '\0';

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
