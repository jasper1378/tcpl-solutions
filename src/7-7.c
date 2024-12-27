#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

#define FLAG_EXCEPT 0x1
#define FLAG_NAME 0x2
#define FLAG_NUMBER 0x4

int getline(FILE *file, char *line, int max);
int do_find(const char *pattern, FILE *file, const char *name, int flags);

int getline(FILE *file, char *line, int lim) {
  int c, i;

  i = 0;
  while (--lim > 0 && (c = getc(file)) != EOF && c != '\n')
    line[i++] = c;
  if (c == '\n')
    line[i++] = c;
  line[i] = '\0';
  return i;
}

int do_find(const char *pattern, FILE *file, const char *name, int flags) {
  int found;
  char line[MAXLINE];
  long lineno;

  found = 0;
  lineno = 0;

  while (getline(file, line, MAXLINE) > 0) {
    ++lineno;
    if ((strstr(line, pattern) != NULL) != (flags & FLAG_EXCEPT)) {
      if ((flags & FLAG_NAME) && *name != '\0') {
        printf("%s:", name);
      }
      if (flags & FLAG_NUMBER) {
        printf("%ld:", lineno);
      }
      printf("%s", line);
      ++found;
    }
  }
  return found;
}

int main(int argc, char *argv[]) {
  int ai;
  char *pattern;
  int flags;
  int found;
  FILE *f;
  int c;

  ai = 1;
  flags = 0x0;
  found = 0;

  for (; ai < argc && *(argv[ai]) == '-'; ++ai) {
    while ((c = *(++(argv[ai])))) {
      switch (c) {
      case 'x': {
        flags |= FLAG_EXCEPT;
      } break;
      case 'f': {
        flags |= FLAG_NAME;
      } break;
      case 'n': {
        flags |= FLAG_NUMBER;
      } break;
      default: {
        printf("find: illegal option %c\n", c);
        found = -1;
        goto goto_out;
      } break;
      }
    }
  }
  if (ai == argc) {
    printf("Usage: find -x -n -f pattern files\n");
  } else {
    pattern = argv[ai];
    ++ai;

    if (ai == argc) {
      found = do_find(pattern, stdin, "", flags);
    } else {
      for (; ai < argc; ++ai) {
        f = fopen(argv[ai], "r");
        found += do_find(pattern, f, argv[ai], flags);
        fclose(f);
      }
    }
  }
goto_out:
  return found;
}
