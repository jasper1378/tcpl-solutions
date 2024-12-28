#include <stdio.h>
#include <string.h>

#define PAGEWIDTH 80
#define PAGEHEIGHT 24

#define MAYBE_REMOVE_NEWLINE(s)                                                \
  do {                                                                         \
    (s)[strcspn((b), "\n")] = '\0';                                            \
  } while (0);

int main(int argc, char *argv[]) {
  char b[PAGEWIDTH];
  FILE *f;
  int p;
  int l;
  int i;

  for (i = 1; i < argc; ++i) {
    f = fopen(argv[i], "r");
    p = 0;
    l = 0;
    while (fgets(b, PAGEWIDTH, f) != NULL) {
      MAYBE_REMOVE_NEWLINE(b);
      if (++l > PAGEHEIGHT || p == 0) {
        ++p;
        l = 1;
        if (!(i == 1 && p == 1)) {
          printf("\n----------\n\n");
        }
        printf("\"%s\", page %d\n\n", argv[i], p);
      }
      puts(b);
    }
    fclose(f);
  }
  return 0;
}
