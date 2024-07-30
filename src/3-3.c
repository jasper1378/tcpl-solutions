#include <ctype.h>

int expand(const char *s1, char *s2) {
  const char *r;
  char *w;
  char b;
  char e;
  char i;

  r = s1;
  w = s2;

  for (; *r != '\0'; ++r) {
    if (*r == '-' && !(r == s1 || *(r + 1) == '\0')) {
      b = *(r - 1);
      e = *(r + 1);
      if (isalnum(b) && isalnum(e)) {
        for (i = b + 1; i < e; ++i) {
          *w++ = i;
        }
      } else {
        return -1;
      }
    } else {
      *w++ = *r;
    }
  }
  *w = '\0';
  return 0;
}
