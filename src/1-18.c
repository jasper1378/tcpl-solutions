#include <stdio.h>

#define MAXLINE 100

int getline(char *buf, int size, int *eof) {
  int i;
  int ch;

  i = 0;

  for (; (ch = getchar()) != EOF && ch != '\n';) {
    if (i < (size - 1)) {
      buf[i] = ch;
      ++i;
    }
  }
  buf[i] = '\0';
  *eof = ch == EOF;
  return i;
}

int main() {
  char line[MAXLINE];
  int len;
  int eof;
  int i;

  eof = 0;

  while (!eof) {
    len = getline(line, MAXLINE, &eof);
    for (; len-- > 0 && (line[len] == ' ' || line[len] == '\t');)
      ;
    for (i = 0; i < (len + 1); ++i) {
      putchar(line[i]);
    }
    putchar('\n');
  }
}
