/* I am aware that we haven't "learned" about malloc() and friends yet. However,
 * to solve this question using the stack allocator from the sorting program
 * in 5.6 (as suggested by K&R), every line of input must be stored at once.
 * Gross! */

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
  struct node *next;
  char *data;
  int size;
};

struct queue {
  struct node *head;
  struct node *tail;
  int len;
};

void q_init(struct queue *q) {
  q->head = NULL;
  q->tail = NULL;
}

int q_push(struct queue *q, char *data, int size) {
  struct node *n;

  n = malloc(sizeof(struct node));
  if (!n) {
    return EXIT_FAILURE;
  }

  n->next = NULL;
  n->data = data;
  n->size = size;

  if (q->tail == NULL) {
    q->head = n;
    q->tail = n;
  } else {
    q->tail->next = n;
    q->tail = n;
  }

  ++q->len;

  return EXIT_SUCCESS;
}

int q_pop(struct queue *q, char **data, int *size) {
  struct node *n;

  if (q->head == NULL) {
    return EXIT_FAILURE;
  } else {
    n = q->head;
    q->head = q->head->next;
    if (q->head == NULL) {
      q->tail = NULL;
    }
  }

  --q->len;

  *data = n->data;
  *size = n->size;

  free(n);

  return EXIT_SUCCESS;
}

int q_len(struct queue *q) { return q->len; }

int peek() {
  int c;

  c = getchar();
  ungetc(c, stdin);
  return c;
}

char *getline(int *len) {
  char *b;
  int l;
  int c;
  int i;

  if (peek() == EOF) {
    *len = -1;
    return NULL;
  }

  l = 32;
  b = malloc(sizeof(char) * l);

  for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i) {
    while (i >= (l - 1)) {
      l *= 2;
      b = realloc(b, sizeof(char) * l);
    }
    b[i] = c;
  }

  b[i] = '\0';

  *len = l;
  return b;
}

int main(int argc, char **argv) {
  int n;
  struct queue q;
  char *b;
  int l;

  if (argc == 1) {
    n = 10;
  } else if (argc == 2) {
    if (argv[1][0] != '-') {
      return EXIT_FAILURE;
    }
    if (!isdigit(argv[1][1])) {
      return EXIT_FAILURE;
    }

    n = atoi(&argv[1][1]);
  } else {
    return EXIT_FAILURE;
  }

  q_init(&q);

  for (;;) {
    b = getline(&l);
    if (b == NULL) {
      break;
    }
    q_push(&q, b, l);
    if (q_len(&q) > n) {
      q_pop(&q, &b, &l);
      free(b);
    }
  }

  while (q_len(&q) > 0) {
    q_pop(&q, &b, &l);
    printf("%s\n", b);
    free(b);
  }

  return EXIT_SUCCESS;
}
