#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int next_tabstop(int tab_start, int tab_every, int pos) {
  if (pos < tab_start) {
    return tab_start;
  } else {
    return (tab_start + (tab_every * ((pos - tab_start) / tab_every + 1)));
  }
}

void detab(int tab_start, int tab_every) {
  int c;
  int p;
  int i;
  int t;

  p = 0;

  while ((c = getchar()) != EOF) {
    if (c == '\t') {
      putchar(' ');
      ++p;
      t = next_tabstop(tab_start, tab_every, p);
      for (i = p; i < t; ++i) {
        putchar(' ');
        ++p;
      }
    } else {
      putchar(c);
      if (c == '\n') {
        p = 0;
      } else {
        ++p;
      }
    }
  }
}

void entab(int tab_start, int tab_every) {
  int c;
  int p;
  int i;
  int n;

  p = 0;

  for (;;) {
    n = 0;
    while ((c = getchar()) == ' ') {
      ++n;
    }
    for (i = p, p += n; (i + n) > next_tabstop(tab_start, tab_every, i);
         n -= (next_tabstop(tab_start, tab_every, i) - i),
        i = next_tabstop(tab_start, tab_every, i)) {
      putchar('\t');
    }
    for (; n > 0; --n) {
      putchar(' ');
    }
    if (c == EOF) {
      break;
    } else {
      putchar(c);
      if (c == '\n') {
        p = 0;
      } else {
        ++p;
      }
    }
  }
}

int main(int argc, char **argv) {
  int tab_start;
  int tab_every;

  if (argc == 1) {
    tab_start = 8;
    tab_every = 8;
  } else if (argc == 3) {
    if (argv[1][0] != '-') {
      return EXIT_FAILURE;
    }
    if (!isdigit(argv[1][1])) {
      return EXIT_FAILURE;
    }
    tab_start = atoi(&argv[1][1]);

    if (argv[2][0] != '+') {
      return EXIT_FAILURE;
    }
    if (!isdigit(argv[2][1])) {
      return EXIT_FAILURE;
    }
    tab_every = atoi(&argv[2][1]);
  } else {
    return EXIT_FAILURE;
  }
#if DETAB
  detab(tab_start, tab_every);
#elif ENTAB
  entab(tab_start, tab_every);
#endif
}
