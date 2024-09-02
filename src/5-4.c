#include <stdio.h>
#include <string.h>

#define MAXSTR 100

int strend(const char *s, const char *t) {
  const char *u;

  for (; *s != '\0'; ++s) {
    for (u = s; (*u == *t) && *u != '\0' && *t != '\0'; ++u, ++t)
      ;
    if (*u == '\0' && *t == '\0') {
      return 1;
    }
  }
  return 0;
}

int main() {
  char s[MAXSTR];
  char t[MAXSTR];

  while (fgets(s, MAXSTR, stdin) != NULL && fgets(t, MAXSTR, stdin) != NULL) {
    s[strcspn(s, "\n")] = '\0';
    t[strcspn(t, "\n")] = '\0';
    printf("%d\n", strend(s, t));
  }

  return 0;
}
