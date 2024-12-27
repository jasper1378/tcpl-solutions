#include <stdio.h>
#include <string.h>

#define MAXLINE 1024

int main(int argc, char *argv[]) {
  FILE *f1;
  FILE *f2;
  char l1[MAXLINE];
  char l2[MAXLINE];
  char *r1;
  char *r2;

  if (argc != 3) {
    return 1;
  }
  if ((f1 = fopen(argv[1], "r")) == NULL) {
    return 1;
  }
  if ((f2 = fopen(argv[2], "r")) == NULL) {
    return 1;
  }

  for (;;) {
    r1 = fgets(l1, MAXLINE, f1);
    r2 = fgets(l2, MAXLINE, f2);
    if (r1 == NULL && r2 == NULL) {
      return 0;
    } else if (r1 == NULL) {
      printf("> %s", l2);
      return 0;
    } else if (r2 == NULL) {
      printf("< %s", l1);
      return 0;
    } else {
      if (strcmp(l1, l2) != 0) {
        printf("< %s", l1);
        printf("---\n");
        printf("> %s", l2);
        return 0;
      }
    }
  }

  /* fclose(f2); */
  /* fclose(f1); */
}
