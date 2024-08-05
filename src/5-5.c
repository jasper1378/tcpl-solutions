#include <stddef.h>

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
