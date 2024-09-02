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

int main() {
  char s[BUFSIZE];
  int i;

  fgets(s, BUFSIZE, stdin);
  s[strcspn(s, "\n")] = '\0';
  printf("read: %s\n", s);
  ungets(s);
  printf("ungets: %s\n", s);
  for (i = 0; bufp > 0; ++i) {
    s[i] = getch();
  }
  s[i] = '\0';
  printf("read: %s\n", s);

  return 0;
}
