#include <stdio.h>
#include <string.h>

#define MAXSTR 100

int strindex(const char *s, const char *t) {
  int r;
  int i;
  int j;
  int k;

  r = -1;

  for (i = 0; s[i] != '\0'; ++i) {
    for (j = i, k = 0; s[j] != '\0' && t[k] != '\0' && s[j] == t[k]; ++j, ++k)
      ;
    if (k > 0 && t[k] == '\0') {
      r = i;
    }
  }

  return r;
}

int main() {
  char s[MAXSTR];
  char t[MAXSTR];

  while (fgets(s, MAXSTR, stdin) != NULL && fgets(t, MAXSTR, stdin) != NULL) {
    s[strcspn(s, "\n")] = '\0';
    t[strcspn(t, "\n")] = '\0';
    printf("%d\n", strindex(s, t));
  }

  return 0;
}
