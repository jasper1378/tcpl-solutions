#include <ctype.h>
#include <math.h>
#include <stdio.h>

int getch(void);
void ungetch(int);

int getfloat(double *pn) {
  int c;
  int s;
  double p;
  int e;
  int es;

  s = 1;
  es = 1;

  while (isspace(c = getch())) {
  }

  if (c == '+' || c == '-') {
    s = (c == '-') ? -1 : 1;
    c = getch();
  }

  if (c == EOF) {
    return EOF;
  } else if (isdigit(c)) {
  } else {
    return 0;
  }

  for (*pn = 0; isdigit(c); c = getch()) {
    *pn = *pn * 10 + (c - '0');
  }

  if (c == '.') {
    c = getch();
    for (p = 1.0; isdigit(c); c = getch()) {
      *pn += (c - '0') / (p *= 10);
    }
  }

  if (c == 'e' || c == 'E') {
    c = getch();
    if (c == '+' || c == '-') {
      es = (c == '-') ? -1 : 1;
      c = getch();
    }
    for (e = 0; isdigit(c); c = getch()) {
      e = e * 10 + (c - '0');
    }
    *pn *= pow(10, es * e);
  }

  *pn *= s;

  return 1;
}
