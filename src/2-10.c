#include <stdio.h>

char lower(char c) {
  return ((c >= 'A' && c <= 'Z') ? (c + ('a' - 'A')) : (c));
}

int main() {
  int c;

  while ((c = getchar()) != EOF) {
    putchar(lower(c));
  }

  return 0;
}
