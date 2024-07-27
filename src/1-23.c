#include <stdio.h>

int peek() {
  int ch;

  ch = getchar();
  ungetc(ch, stdin);
  return ch;
}

enum state {
  IN_NONE,
  IN_COMMENT,
  IN_STRING,
  IN_CHAR,
};

int main() {
  int state;
  int ch;
  int last;

  state = IN_NONE;

  while ((ch = getchar()) != EOF) {
    if (state == IN_COMMENT) {
      if (ch == '*' && peek() == '/') {
        ch = getchar();
        state = IN_NONE;
      }
    } else {
      switch (state) {
      case IN_NONE: {
        if (ch == '/') {
          if (peek() == '*') {
            ch = getchar();
            state = IN_COMMENT;
          } else if (peek() == '/') {
            while ((ch = getchar()) != EOF && ch != '\n')
              ;
          }
        } else {
          putchar(ch);
          if (ch == '"') {
            state = IN_STRING;
          } else if (ch == '\'') {
            state = IN_CHAR;
          }
        }
      } break;
      case IN_STRING: {
        putchar(ch);
        if (ch == '"' && last != '\\') {
          state = IN_NONE;
        }
      } break;
      case IN_CHAR: {
        putchar(ch);
        if (ch == '\'' && last != '\'') {
          state = IN_NONE;
        }
      } break;
      }
    }
    last = ch;
  }
}
