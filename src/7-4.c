#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

#define MAXSTR 100

#define ungetchar(c) ungetc(c, stdin);

int minscanf(const char *, ...);

int minscanf(const char *fmt, ...) {
  va_list ap;
  int r;
  const char *p;
  char c;

  r = 0;
  va_start(ap, fmt);

  for (p = fmt; *p != '\0'; ++p) {
    if (isspace(*p)) {
      while (isspace(c = getchar()))
        ;
      ungetchar(c);
    } else if (*p == '%' && *++p != '%') {
      ++r;
      switch (*p) {
      case 'd': {
        scanf("%d", va_arg(ap, int *));
      } break;
      case 'f': {
        scanf("%f", va_arg(ap, float *));
      } break;
      case 's': {
        scanf("%s", va_arg(ap, char *));
      } break;
      default: {
        --r;
        goto goto_out;
      } break;
      }
    } else {
      if ((c = getchar()) != *p) {
        ungetchar(c);
        goto goto_out;
      }
    }
  }

goto_out:
  va_end(ap);
  if (r == 0 && c == EOF) {
    return EOF;
  } else {
    return r;
  }
}

int main() {
  int i;
  float f;
  char s[MAXSTR];
  int r;

  printf("scanf(\"int %%d, flt %%f, str %%s, pct %%%%, white	"
         "space\",...)\n");
  r = minscanf("int %d, flt %f, str %s, pct %%, white	space", &i, &f, &s);
  printf("int %d, flt %f, str %s, ret %d\n", i, f, s, r);
  return 0;
}

/**/

void minprintf(char *fmt, ...) {
  va_list ap; /* points to each unnamed arg in turn */
  char *p, *sval;
  int ival;
  double dval;

  va_start(ap, fmt); /* make ap point to 1st unnamed arg */
  for (p = fmt; *p; p++) {
    if (*p != '%') {
      putchar(*p);
      continue;
    }
    switch (*++p) {
    case 'd':
      ival = va_arg(ap, int);
      printf("%d", ival);
      break;
    case 'f':
      dval = va_arg(ap, double);
      printf("%f", dval);
      break;
    case 's':
      for (sval = va_arg(ap, char *); *sval; sval++)
        putchar(*sval);
      break;
    default:
      putchar(*p);
      break;
    }
  }
  va_end(ap); /* clean up when done */
}
