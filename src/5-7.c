#include <stdio.h>
#include <string.h>

#define MAXBUF 10000
#define MAXLEN 1000
#define MAXLINE 100

int getline(char s[], int lim) {
  int c, i;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return i;
}

int readlines(char *lineptr[], int maxlines, char *buf) {
  int len;
  int nlines;
  char *p;
  char line[MAXLEN];

  nlines = 0;
  p = buf;
  while ((len = getline(line, MAXLEN)) > 0)
    if (nlines >= maxlines || (buf + MAXBUF - p < len)) {
      return -1;
    } else {
      line[len - 1] = '\0';
      strcpy(p, line);
      lineptr[nlines++] = p;
      p += len;
    }
  return nlines;
}

int main() {
  char *lineptr[MAXLINE];
  char buf[MAXBUF];
  int nlines;
  int i;

  nlines = readlines(lineptr, MAXLINE, buf);

  for (i = 0; i < nlines; ++i) {
    puts(lineptr[i]);
  }

  return 0;
}
