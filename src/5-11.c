#include <stdio.h>
#include <stdlib.h>

#define TAB_SIZE 8

#define NEXT_TABSTOP(pos_) ((((pos_) / TAB_SIZE) * TAB_SIZE) + TAB_SIZE)

int next_tabstop(int argc, char **argv, int *argi, int pos) {
  int t;

  static int pos_last = 0;

  if (argc == 1) {
    return NEXT_TABSTOP(pos);
  } else {
    if (pos_last > pos) {
      *argi = 0;
    }
    pos_last = pos;

    if (*argi == 0) {
      ++*argi;
    }

    for (; *argi < argc && pos >= (t = atoi(argv[*argi])); ++*argi)
      ;

    if (*argi == argc) {
      return pos;
    } else {
      return t;
    }
  }
}

void detab(int argc, char **argv) {
  int argi;
  int c;
  int p;
  int i;
  int t;

  p = 0;

  while ((c = getchar()) != EOF) {
    if (c == '\t') {
      putchar(' ');
      ++p;
      t = next_tabstop(argc, argv, &argi, p);
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

void entab(int argc, char **argv) {
  int argi;
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
    for (i = p, p += n; (i + n) > next_tabstop(argc, argv, &argi, i);
         n -= (next_tabstop(argc, argv, &argi, i) - i),
        i = next_tabstop(argc, argv, &argi, i)) {
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
#if DETAB
  detab(argc, argv);
#elif ENTAB
  entab(argc, argv);
#endif
}
