#include <stdio.h>
#include <stdlib.h>

#define DELIMS_MAX_SIZE 100

int peek() {
  int ch;

  ch = getchar();
  ungetc(ch, stdin);
  return ch;
}

struct stack {
  char *buf;
  int size;
  int idx;
};

int stack_init(struct stack *s, int size) {
  s->buf = (char *)malloc(sizeof(char) * size);
  s->size = size;
  s->idx = -1;
  return (s->buf == NULL ? -1 : 0);
}

void stack_free(struct stack *s) {
  if (s->buf) {
    free(s->buf);
  }
}

int stack_full(struct stack *s) { return !(s->idx + 1 < s->size); }

int stack_empty(struct stack *s) { return !(s->idx >= 0); }

int stack_push(struct stack *s, char c) {
  if (!stack_full(s)) {
    s->buf[++(s->idx)] = c;
    return 0;
  } else {
    return EOF;
  }
}

int stack_pop(struct stack *s) {
  if (!stack_empty(s)) {
    return s->buf[(s->idx)--];
  } else {
    return EOF;
  }
}

int stack_peep(struct stack *s) {
  if (!stack_empty(s)) {
    return s->buf[(s->idx)];
  } else {
    return EOF;
  }
}

int main() {
  struct stack delims;
  int in_string;
  int in_char;
  int in_comment;
  int last;
  int ch;
  int fail;

  stack_init(&delims, DELIMS_MAX_SIZE);
  in_string = 0;
  in_char = 0;
  in_comment = 0;
  last = EOF;
  fail = 0;

  while ((ch = getchar()) != EOF && !fail) {
    if (in_string) {
      if (ch == '"' && last != '\\') {
        in_string = 0;
      }
    } else if (in_char) {
      if (ch == '\'' && last != '\\') {
        in_char = 0;
      }
    } else if (in_comment) {
      if (ch == '*' && peek() == '/') {
        ch = getchar();
        in_comment = 0;
      }
    } else {
      switch (ch) {
      case '/': {
        if (peek() == '*') {
          ch = getchar();
          in_comment = 1;
        } else if (peek() == '/') {
          ch = getchar();
          while ((ch = getchar()) != EOF && ch != '\n')
            ;
        }
      } break;
      case '"': {
        in_string = 1;
      } break;
      case '\'': {
        in_char = 1;
      } break;
      case '(': {
        if (stack_push(&delims, '(') == EOF) {
          fail = 1;
        }
      } break;
      case ')': {
        if (stack_peep(&delims) == '(') {
          stack_pop(&delims);
        } else {
          fail = 1;
        }
      } break;
      case '[': {
        if (stack_push(&delims, '[') == EOF) {
          fail = 1;
        }
      } break;
      case ']': {
        if (stack_peep(&delims) == '[') {
          stack_pop(&delims);
        } else {
          fail = 1;
        }
      } break;
      case '{': {
        if (stack_push(&delims, '{') == EOF) {
          fail = 1;
        }
      } break;
      case '}': {
        if (stack_peep(&delims) == '{') {
          stack_pop(&delims);
        } else {
          fail = 1;
        }
      } break;
      }
    }
    last = ch;
  }

  fail = fail || (!stack_empty(&delims) || in_string || in_char || in_comment);

  stack_free(&delims);

  if (fail) {
#if PRINT
    printf("FAILURE\n");
#endif
    return EXIT_FAILURE;
  } else {
#if PRINT
    printf("SUCCESS\n");
#endif
    return EXIT_SUCCESS;
  }
}
