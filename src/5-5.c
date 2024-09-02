#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define MAXSTR 100

char *strncpy(char *dest, const char *src, size_t count) {
  char *r;

  r = dest;
  for (; *src != '\0' && count > 0; ++src, ++dest, --count) {
    *dest = *src;
  }
  for (; count > 0; ++dest, --count) {
    *dest = '\0';
  }

  return r;
}

char *strncat(char *dest, const char *src, size_t count) {
  char *r;

  r = dest;
  for (; *dest != '\0'; ++dest)
    ;
  for (; *src != '\0' && count > 0; ++src, ++dest, --count) {
    *dest = *src;
  }
  *dest = '\0';

  return r;
}

int strncmp(const char *lhs, const char *rhs, size_t count) {
  for (; *lhs != '\0' && *rhs != '\0' && count > 0; ++lhs, ++rhs, --count) {
    if (*lhs != *rhs) {
      break;
    }
  }

  if ((*lhs == '\0' && *rhs == '\0') || count == 0) {
    return 0;
  } else {
    return *lhs - *rhs;
  }
}

int main() {
  char s[MAXSTR];
  char t[MAXSTR];
  int n;

  fgets(s, MAXSTR, stdin);
  fgets(t, MAXSTR, stdin);
  scanf("%d", &n);
  s[strcspn(s, "\n")] = '\0';
  t[strcspn(t, "\n")] = '\0';
  strncat(s, t, n);
  printf("strncat: %s\n", s);
  strncpy(s, t, n);
  printf("strncpy: %s\n", s);
  printf("strcmp: %d\n", strncmp(s, t, n));

  return 0;
}
