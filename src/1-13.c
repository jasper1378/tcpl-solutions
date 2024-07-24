#include <stdio.h>
#include <stdlib.h>

int main() {
  int maxl;
  int maxc;
  int size;
  int *hist;
  int ch;
  int len;
  int in;
  int i;
  int j;

  maxl = 0;
  maxc = 0;

  size = 10;
  hist = (int *)calloc(size, sizeof(int));

  len = 0;
  in = 0;

  while ((ch = getchar()) != EOF) {
    if (ch == ' ' || ch == '\t' || ch == '\n') {
      if (in) {
        in = 0;
        if (len > maxl) {
          maxl = len;
        }
        if (len > size) {
          size = len * 2;
          hist = (int *)realloc(hist, size);
        }
        ++hist[len - 1];
        if (hist[len - 1] > maxc) {
          maxc = hist[len - 1];
        }
        len = 0;
      }
    } else {
      in = 1;
      ++len;
    }
  }

  /* horizontal */
  /*
  for (i = 0; i < maxl; ++i) {
    printf("%d ", i + 1);
    for (j = 0; j < hist[i]; ++j) {
      putchar('*');
    }
    putchar('\n');
  }
  */

  /* vertical */
  for (i = 0; i < maxl; ++i) {
    printf("%d ", i + 1);
  }
  putchar('\n');
  for (i = 0; i < maxc; ++i) {
    for (j = 0; j < maxl; ++j) {
      if (hist[j] >= (i + 1)) {
        putchar('*');
      } else {
        putchar(' ');
      }
      putchar(' ');
    }
    putchar('\n');
  }

  free(hist);
}
