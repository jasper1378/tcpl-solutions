#include <stdio.h>

#define WIDTH 80

int peek() {
  int ch;

  ch = getchar();
  ungetc(ch, stdin);
  return ch;
}

void print(const char *str, int size, int nl) {
  int i;

  for (i = 0; i < size; ++i) {
    putchar(*(str + i));
  }
  if (nl) {
    putchar('\n');
  }
}

int main() {
  char line[WIDTH];
  int length;
  int in_blank;
  int last_blank;
  int eof;
  int ch;
  int pc;
  int i;

  eof = 0;

  while (!eof) {
    for (i = 0, in_blank = 0, last_blank = -1;
         i < WIDTH && (ch = getchar()) != EOF && ch != '\n'; ++i) {
      line[i] = ch;
      if (ch == ' ' || ch == '\t') {
        if (!in_blank) {
          last_blank = i;
        }
        in_blank = 1;
      } else {
        in_blank = 0;
      }
    }
    length = i;
    if (length == WIDTH) {
      pc = peek();
      switch (pc) {
      case ' ':
      case '\t':
        last_blank = -1;
      case '\n':
        getchar();
      }
    }
    eof = (ch == EOF);
    if (ch == '\n' || ch == EOF) {
      print(line, length, 1);
    } else {
      if (last_blank == -1) {
        print(line, length, 1);
      } else {
        print(line, last_blank, 1);
        print(line + last_blank + 1, length - last_blank - 1, 0);
      }
    }
  }
}
