#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define MAXVAL 100
#define BUFSIZE 100

enum op {
  OP_ADD = '+',
  OP_MUL = '*',
  OP_SUB = '-',
  OP_DIV = '/',
  OP_MOD = '%',
  OP_NLN = '\n',
  OP_EOF = EOF,
  OP_NUM,
  OP_UNK,
  OP_GVR,
  OP_SVR,
};

int getop(char[]);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
int isnum(char[]);

int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
int bufp = 0;

int main() {
  int type;
  double op1;
  double op2;
  char s[MAXOP];
  double var[26] = {0};

  while ((type = getop(s)) != OP_EOF) {
    switch (type) {
    case OP_NUM:
      push(atof(s));
      break;
    case OP_ADD:
      op2 = pop();
      op1 = pop();
      push(op1 + op2);
      break;
    case OP_MUL:
      op2 = pop();
      op1 = pop();
      push(op1 * op2);
      break;
    case OP_SUB:
      op2 = pop();
      op1 = pop();
      push(op1 - op2);
      break;
    case OP_DIV:
      op2 = pop();
      op1 = pop();
      if (op2 != 0.0)
        push(op1 / op2);
      else
        printf("error: zero divisor\n");
      break;
    case OP_MOD:
      op2 = pop();
      op1 = pop();
      if (op2 != 0.0)
        push((long)op1 % (long)op2);
      else
        printf("error: zero divisor\n");
      break;
    case OP_GVR:
      push(var[*s - 'a']);
      break;
    case OP_SVR:
      op1 = pop();
      var[s[1] - 'a'] = op1;
      push(op1);
      break;
    case OP_NLN:
      printf("\t%.8g\n", pop());
      break;
    case OP_UNK:
      printf("error: unknown command %s\n", s);
      break;
    }
  }

  return 0;
}

void push(double f) {
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

double pop(void) {
  if (sp > 0)
    return val[--sp];
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

int getop(char s[]) {
  int i;
  int c;
  int d;

  for (d = 0; !d;) {
    switch (c = getch()) {
    case ' ':
    case '\t':
      break;
    case '\n':
    case EOF:
      return c;
      break;
    default:
      ungetch(c);
      d = 1;
      break;
    }
  }

  for (i = 0, d = 0; !d;) {
    switch (c = getch()) {
    case ' ':
    case '\t':
      d = 1;
      break;
    case '\n':
    case EOF:
      ungetch(c);
      d = 1;
      break;
    default:
      s[i++] = c;
      break;
    }
  }
  s[i] = '\0';

  if (i == 1) {
    switch (s[0]) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
      return s[0];
      break;
    }
  }
  if (isnum(s)) {
    return OP_NUM;
  }
  if (i == 1 && *s >= 'a' && *s <= 'z') {
    return OP_GVR;
  }
  if (i == 2 && s[0] == '=' && s[1] >= 'a' && s[2] <= 'z') {
    return OP_SVR;
  }
  return OP_UNK;
}

int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else {
    buf[bufp++] = c;
  }
}

int isnum(char s[]) {
  if (*s == '-' || *s == '+') {
    ++s;
  }
  for (; *s != '\0'; ++s) {
    if (!(isdigit(*s) || *s == '.')) {
      return 0;
    }
  }
  return 1;
}
