#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EXIT_WITH_ERROR(msg_)                                                  \
  do {                                                                         \
    fprintf(stderr, "ERROR: " msg_ "\n");                                      \
    exit(EXIT_FAILURE);                                                        \
  } while (0);

#define STACKSIZE 100

typedef struct stack {
  double b[STACKSIZE];
  int i;
} stack;

void s_init(stack *s) { s->i = 0; }

double s_pop(stack *s) {
  if (s->i > 0) {
    return s->b[--(s->i)];
  } else {
    EXIT_WITH_ERROR("stack empty");
  }
}

void s_push(stack *s, double v) {
  if (s->i < STACKSIZE) {
    s->b[(s->i)++] = v;
  } else {
    EXIT_WITH_ERROR("stack full");
  }
}

enum {
  OP_ADD = 0,
  OP_SUB = 1,
  OP_MUL = 2,
  OP_DIV = 3,
  OP_MOD = 4,
  OP_POW = 5,
  OP_UNK,
  OP_NUM,
};

double oadd(double x, double y) { return x + y; }
double osub(double x, double y) { return x - y; }
double omul(double x, double y) { return x * y; }
double odiv(double x, double y) { return x / y; }
double omod(double x, double y) { return (long)x % (long)y; }
double opow(double x, double y) { return pow(x, y); }

typedef double (*op_func_t)(double, double);
static const op_func_t op_funcs[] = {oadd, osub, omul, odiv, omod, opow};

int isspace(int ch) {
  switch (ch) {
  case ' ':
  case '\f':
  case '\n':
  case '\r':
  case '\t':
  case '\v':
    return 1;
    break;
  default:
    return 0;
    break;
  }
}

int isdigit(int ch) { return (ch >= '0' && ch <= '9'); }

double atof(const char *str) {
  int s;
  double p;
  int es;
  int e;
  double r;

  s = 1;
  es = 1;
  e = 0;
  r = 0;

  for (; isspace(*str); ++str)
    ;

  if (*str == '-' || *str == '+') {
    s = (*str == '-') ? -1 : 1;
    ++str;
  }

  if (!isdigit(*str)) {
    goto exit_with_error;
  }

  for (; isdigit(*str); ++str) {
    r = r * 10 + (*str - '0');
  }

  if (*str == '.') {
    ++str;
    if (!isdigit(*str)) {
      goto exit_with_error;
    }
    for (p = 10; isdigit(*str); ++str, p *= 10) {
      r += (*str - '0') / p;
    }
  }

  if (*str == 'e' || *str == 'E') {
    ++str;

    if (*str == '-' || *str == '+') {
      es = (*str == '-') ? -1 : 1;
      ++str;
    }

    if (!isdigit(*str)) {
      goto exit_with_error;
    }

    for (; isdigit(*str); ++str) {
      e = e * 10 + (*str - '0');
    }

    r *= pow(10, es * e);
  }

  r *= s;

  return r;

exit_with_error:;
  EXIT_WITH_ERROR("invalid float format");
}

int op(const char *str) {
  if (*str == '\0') {
    return OP_UNK;
  } else {
    if (*(str + 1) == '\0') {
      switch (*str) {
      case '+':
        return OP_ADD;
        break;
      case '-':
        return OP_SUB;
        break;
      case '*':
        return OP_MUL;
        break;
      case '/':
        return OP_DIV;
        break;
      case '%':
        return OP_MOD;
        break;
      case '^':
        return OP_POW;
        break;
      }
    }

    return OP_NUM;
  }
}

int main(int argc, char **argv) {
  stack s;
  int i;
  int o;
  double o1;
  double o2;

  s_init(&s);

  for (i = 1; i < argc; ++i) {
    switch (o = op(argv[i])) {
    case OP_UNK:
      EXIT_WITH_ERROR("invalid op");
      break;
    case OP_NUM:
      s_push(&s, atof(argv[i]));
      break;
    case OP_ADD:
    case OP_SUB:
    case OP_MUL:
    case OP_DIV:
    case OP_MOD:
    case OP_POW:
      o2 = s_pop(&s);
      o1 = s_pop(&s);
      s_push(&s, op_funcs[o](o1, o2));
      break;
    }
  }

  printf("%lf\n", s_pop(&s));
}
