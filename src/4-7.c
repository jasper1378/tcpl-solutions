#include <stdio.h>
#include <string.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else {
    buf[bufp++] = c;
  }
}

void ungets(const char *s) {
  int i;

  for (i = strlen(s); i-- > 0;) {
    ungetch(s[i]);
  }
}
