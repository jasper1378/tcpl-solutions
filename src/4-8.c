#include <stdio.h>

#define BUFSIZE 1

char buf;
int bufp = 0;

int getch(void) {
  if (bufp > 0) {
    --bufp;
    return buf;
  } else {
    return getchar();
  }
}

void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else {
    bufp++;
    buf = c;
  }
}

int main() {
  int c;
  c = getch();
  printf("get: %c\n", c);
  ungetch(c);
  printf("unget: %c\n", c);
  c = getch();
  printf("get: %c\n", c);

  return 0;
}
