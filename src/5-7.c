#include <string.h>

char *alloc(int n);
void afree(char *p);
int getline(char[], int);

#define MAXLEN 1000
#define MAXBUF 10000

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
