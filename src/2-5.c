#include <stdio.h>
#include <string.h>

#define MAXSTR 100

int any(const char *s1, const char *s2) {
  int i;
  int j;

  for (i = 0; s1[i] != '\0'; ++i) {
    for (j = 0; s2[j] != '\0'; ++j) {
      if (s1[i] == s2[j]) {
        return i;
      }
    }
  }

  return -1;
}

int main() {
  char s1[MAXSTR];
  char s2[MAXSTR];

  while (fgets(s1, MAXSTR, stdin) != NULL && fgets(s2, MAXSTR, stdin) != NULL) {
    s1[strcspn(s1, "\n")] = '\0';
    s2[strcspn(s2, "\n")] = '\0';
    printf("%d\n", any(s1, s2));
  }

  return 0;
}
