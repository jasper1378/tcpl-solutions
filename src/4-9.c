#include <stdio.h>

#define BUFSIZE 100

int buf[BUFSIZE];
int bufp = 0;

int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else {
    buf[bufp++] = c;
  }
}

int main() {
  int c;

  while (bufp < BUFSIZE) {
    ungetch(c = getchar());
    if (c == EOF) {
      break;
    }
  }
  while (bufp > 0) {
    if ((c = getch()) == EOF) {
      fputs("EOF", stdout);
    } else {
      putchar(c);
    }
  }

  return 0;
}
