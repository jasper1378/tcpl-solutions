#include <stdio.h>
#include <string.h>

#define MAXSTR 100

void strcat_(char *s, const char *t) {
  while (*s != '\0')
    ++s;
  while ((*s++ = *t++) != '\0')
    ;
}

int main() {
  char s[MAXSTR];
  char t[MAXSTR];

  while (fgets(s, MAXSTR, stdin) != NULL && fgets(t, MAXSTR, stdin) != NULL) {
    s[strcspn(s, "\n")] = '\0';
    t[strcspn(t, "\n")] = '\0';
    strcat_(s, t);
    puts(s);
  }

  return 0;
}
