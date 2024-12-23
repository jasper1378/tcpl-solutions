/* requires POSIX for `basename` */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libgen.h>

#define do_filter(func)                                                        \
  while ((c = getchar()) != EOF) {                                             \
    putchar(func(c));                                                          \
  }

#define lower() do_filter(tolower)
#define upper() do_filter(toupper)

int main(int argc, char *argv[]) {
  int c;

  (void)argc;

  if (strcmp(basename(argv[0]), "lower") == 0) {
    lower();
  } else if (strcmp(basename(argv[0]), "upper") == 0) {
    upper();
  } else {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
