#include <stdio.h>

#define MAXLINE 100

void reverse(char *s, int n) {
  int i;
  char t;

  for (i = 0; i < (n / 2); ++i) {
    t = s[i];
    s[i] = s[n - (i + 1)];
    s[n - (i + 1)] = t;
  }
}

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

  eof = 0;

  while (!eof) {
    len = getline(line, MAXLINE, &eof);
    reverse(line, len);
    printf("%s\n", line);
  }
}
