#include <string.h>

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
