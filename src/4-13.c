#include <stdio.h>
#include <string.h>

#define MAXSTR 100

void reverse(char s[]) {
  static char *f = NULL;
  static char *b = NULL;
  char c;

  if (!f && !b) {
    f = s;
    b = s + strlen(s) - 1;
  }

  if (f < b) {
    c = *f;
    *f = *b;
    *b = c;
    ++f;
    --b;
    reverse(s);
  } else {
    f = NULL;
    b = NULL;
  }
}

int main() {
  char s[MAXSTR];

  while (fgets(s, MAXSTR, stdin) != NULL) {
    s[strcspn(s, "\n")] = '\0';
    reverse(s);
    puts(s);
  }

  return 0;
}
