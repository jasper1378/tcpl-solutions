#include <stdio.h>

int main() {
  int nb;
  int nt;
  int nl;
  int c;

  nb = 0;
  nt = 0;
  nl = 0;

  while ((c = getchar()) != EOF) {
    switch (c) {
    case ' ':
      ++nb;
      ;
      break;
    case '\t':
      ++nt;
      break;
    case '\n':
      ++nl;
      break;
    }
  }

  printf("blanks = %d, tabs = %d, newlines = %d\n", nb, nt, nl);
}
