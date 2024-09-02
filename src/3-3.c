#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXSTR 100

void expand(const char *s1, char *s2) {
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
        *w++ = *r;
      }
    } else {
      *w++ = *r;
    }
  }
  *w = '\0';
}

int main() {
  char s1[MAXSTR];
  char s2[MAXSTR];

  while (fgets(s1, MAXSTR, stdin) != NULL) {
    s1[strcspn(s1, "\n")] = '\0';
    expand(s1, s2);
    puts(s2);
  }

  return 0;
}
