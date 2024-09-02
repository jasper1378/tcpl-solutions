#include <stdio.h>
#include <string.h>

#define MAXSTR 100

void squeeze(char *s1, const char *s2) {
  const char *r;
  char *w;
  const char *s;

  for (r = s1, w = s1; *r != '\0'; ++r) {
    for (s = s2; *s != '\0'; ++s) {
      if (*s == *r) {
        break;
      }
    }
    if (*s == '\0') {
      *w++ = *r;
    }
  }
  *w = '\0';
}

int main() {
  char s1[MAXSTR];
  char s2[MAXSTR];

  while (fgets(s1, MAXSTR, stdin) != NULL && fgets(s2, MAXSTR, stdin) != NULL) {
    s1[strcspn(s1, "\n")] = '\0';
    s2[strcspn(s2, "\n")] = '\0';
    squeeze(s1, s2);
    puts(s1);
  }

  return 0;
}
