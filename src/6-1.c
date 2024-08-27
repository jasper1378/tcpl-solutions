#include <ctype.h>
#include <stdio.h>

#define WORDSIZE 100

#define getch() getchar()
#define ungetch(ch_) ungetc((ch_), stdin)

int peek() {
  int c;

  c = getch();
  ungetch(c);
  return c;
}

int skip_whitespace() {
  int c;

  if (isspace(peek())) {
    while (isspace(c = getch()))
      ;
    ungetch(c);
    return 1;
  } else {
    return 0;
  }
}

int skip_string() {
  int c;

  if (peek() == '"') {
    c = getch();
    while ((c = getch()) != '"' && c != EOF)
      ;
    return 1;
  } else {
    return 0;
  }
}

int skip_comment() {
  int c;

  if ((c = getch()) == '/') {
    if (peek() == '*') {
      c = getch();
      while ((c = getch()) != EOF) {
        if (c == '*' && peek() == '/') {
          c = getch();
          break;
        }
      }
      return 1;
    } else if (peek() == '/') {
      while ((c = getch()) != EOF && c != '\n')
        ;
      return 1;
    } else {
      ungetch(c);
      return 0;
    }
  } else {
    ungetch(c);
    return 0;
  }
}

int skip_preprocessor() {
  int c;

  if (peek() == '#') {
    while ((c = getch()) != '\n' && c != EOF)
      ;
    return 1;
  } else {
    return 0;
  }
}

void skip() {
  while ((skip_whitespace() + skip_string() + skip_comment() +
          skip_preprocessor()) != 0)
    ;
}

int getword(char *word, int lim) {
  int c;
  int i;

  skip();
  c = getch();

  if (c == EOF) {
    return EOF;
  } else if (isalpha(c) || c == '_') {
    for (i = 0; i < lim && (isalnum(c) || c == '_'); ++i, c = getch()) {
      word[i] = c;
    }
    ungetch(c);
    word[i] = '\0';
    return *word;
  } else {
    *word = '\0';
    return c;
  }
}

int main() {
  char word[WORDSIZE];
  int c;

  while ((c = getword(word, WORDSIZE)) != EOF) {
    if (*word == '\0') {
      printf("%c\n", c);
    } else {
      puts(word);
    }
  }
}
