#include <ctype.h>
#include <stdio.h>

#define MAXOP 100
#define MAXSTR 100
#define MAXVAL 100
#define NUMBER '0'

int getop(double *d);
void push(double);
double pop(void);

int sp = 0;
double val[MAXVAL];

/*
  wow, using scanf is so much more convenient... NOT!!!
 */
int getop(double *d) {
  char c;

  do {
    scanf("%c", &c);
  } while (c != '\n' && isspace(c));
  if (c == '\n') {
    return c;
  }
  ungetc(c, stdin);

  if (scanf("%lf", d) != 1) {
    return c;
  } else {
    return NUMBER;
  }
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

int main() {
  int type;
  double op2;
  double d;

  while ((type = getop(&d)) != EOF) {
    switch (type) {
    case NUMBER:
      push(d);
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0)
        push(pop() / op2);
      else
        printf("error: zero divisor\n");
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("error: unknown command '%c'\n", type);
      break;
    }
  }
  return 0;
}
