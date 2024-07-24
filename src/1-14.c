#include <stdio.h>
#include <stdlib.h>

int main() {
  int max;
  int size;
  int *hist;
  int ch;
  int i;
  int j;

  max = 0;
  size = '~' - '!' + 1;

  hist = (int *)calloc(size, sizeof(int));

  while ((ch = getchar()) != EOF) {
    if (ch >= '!' && ch <= '~') {
      ch -= '!';
      if (ch > max) {
        max = ch;
      }
      if (ch >= size) {
        size = ch;
        hist = (int *)realloc(hist, size);
      }
      ++hist[ch];
    }
  }

  for (i = 0; i <= max; ++i) {
    if (hist[i] != 0) {
      printf("%c ", i + '!');
      for (j = 0; j < hist[i]; ++j) {
        putchar('*');
      }
      putchar('\n');
    }
  }

  free(hist);
}
