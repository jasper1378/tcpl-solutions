#include <stdio.h>

#define LENGTH 81

int getline(char *buf, int size) {
  int i;
  int ch;

  for (i = 0; i < (size - 1) && (ch = getchar()) != EOF && ch != '\n'; ++i) {
    buf[i] = ch;
  }
  buf[i] = '\0';
  return i;
}

int main() {
  int len;
  int ch;
  char buf[LENGTH + 1];

  while ((len = getline(buf, LENGTH + 1)) > 0) {
    if (len >= LENGTH) {
      printf("%s", buf);
      while ((ch = getchar()) != EOF && ch != '\n') {
        putchar(ch);
      }
      putchar('\n');
    }
  }
}
