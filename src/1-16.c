#include <stdio.h>

#define MAXLINE 5

int getline(char line[], int maxline);
void copy(char to[], char from[]);

int main() {
  int len;
  int max;
  char line[MAXLINE];
  char longest[MAXLINE];
  int c;

  max = 0;
  while ((len = getline(line, MAXLINE)) > 0) {
    if (line[len - 1] != '\n') {
      while ((c = getchar()) != EOF && c != '\n') {
        ++len;
      }
      ++len;
    }
    if (len > max) {
      max = len;
      copy(longest, line);
    }
  }
  if (max > 0) {
    printf("%d: %s", max, longest);
  }
  if (longest[((max > MAXLINE) ? MAXLINE : max) - 1] != '\n') {
    putchar('\n');
  }
}

int getline(char s[], int lim) {
  int c;
  int i;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
    s[i] = c;
  }
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return i;
}

void copy(char to[], char from[]) {
  int i;

  i = 0;
  while ((to[i] = from[i]) != '\0') {
    ++i;
  }
}
