#include <stdio.h>
#include <string.h>

#define MAXSTR 100

int escape(char *s, const char *t) {
  for (; *t != '\0'; ++s, ++t) {
    switch (*t) {
    case '\\': {
      *s++ = '\\';
      *s = '\\';
    } break;
    case '\n': {
      *s++ = '\\';
      *s = 'n';
    } break;
    case '\t': {
      *s++ = '\\';
      *s = 't';
    } break;
    default: {
      *s = *t;
    };
    }
  }
  *s = '\0';
  return 0;
}

int unescape(char *s, const char *t) {
  for (; *t != '\0'; ++s, ++t) {
    switch (*t) {
    case '\\': {
      switch (*++t) {
      case '\\': {
        *s = '\\';
      } break;
      case 'n': {
        *s = '\n';
      } break;
      case 't': {
        *s = '\t';
      } break;
      default: {
        return -1;
      };
      }
    } break;
    default: {
      *s = *t;
    } break;
    }
  }
  *s = '\0';
  return 0;
}

int main(int argc, char *argv[]) {
  char s[MAXSTR];
  char t[MAXSTR];

  (void)argv;

  while (fgets(t, MAXSTR, stdin) != NULL) {
    t[strcspn(t, "\n")] = '\0';
    if (argc > 1) {
      unescape(s, t);
    } else {
      escape(s, t);
    }
    puts(s);
  }

  return 0;
}
