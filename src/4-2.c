#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define MAXSTR 100

double atof(const char *s) {
  double val;
  double power;
  int i;
  int sign;
  double eval;
  int esign;

  for (i = 0; isspace(s[i]); ++i)
    ;
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-') {
    ++i;
  }
  for (val = 0.0; isdigit(s[i]); ++i) {
    val = 10.0 * val + (s[i] - '0');
  }
  if (s[i] == '.') {
    ++i;
  }
  for (power = 1.0; isdigit(s[i]); ++i) {
    val = 10.0 * val + (s[i] - '0');
    power *= 10;
  }
  if (s[i] == 'e' || s[i] == 'E') {
    ++i;
  }
  esign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-') {
    ++i;
  }
  for (eval = 0.0; isdigit(s[i]); ++i) {
    eval = 10.0 * eval + (s[i] - '0');
  }
  return (sign * val / power) * pow(10, esign * eval);
}

int main() {
  char s[MAXSTR];

  while (fgets(s, MAXSTR, stdin) != NULL) {
    s[strcspn(s, "\n")] = '\0';
    printf("%e\n", atof(s));
  }

  return 0;
}
