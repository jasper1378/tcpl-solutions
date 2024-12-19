#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100

#define getch() getchar()
#define ungetch(c_) ungetc((c_), stdin)

struct tnode {
  char *word;
  int count;
  struct tnode *left;
  struct tnode *right;
};

int getword(char *, int);
struct tnode *addtree(struct tnode *, char *, int *);
struct tnode *talloc(void);
char *strdup(char *);
struct tnode *treecpy(struct tnode *, struct tnode *);
int comp_tnode(const void *, const void *);

int getword(char *word, int lim) {
  int c;
  char *w;

  w = word;

  while (isspace(c = getch()))
    ;
  if (c == EOF) {
    return EOF;
  } else {
    *w++ = c;
  }
  for (; --lim > 0; w++)
    if (isspace(*w = getch()) || *w == EOF) {
      ungetch(*w);
      break;
    }
  *w = '\0';
  return word[0];
}

struct tnode *addtree(struct tnode *p, char *w, int *nc) {
  int cond;

  if (p == NULL) {
    p = talloc();
    p->word = strdup(w);
    p->count = 1;
    p->left = p->right = NULL;
    ++*nc;
  } else if ((cond = strcmp(w, p->word)) == 0) {
    p->count++;
  } else if (cond < 0) {
    p->left = addtree(p->left, w, nc);
  } else {
    p->right = addtree(p->right, w, nc);
  }
  return p;
}

struct tnode *talloc(void) {
  return (struct tnode *)malloc(sizeof(struct tnode));
}

char *strdup(char *s) {
  char *p;

  p = (char *)malloc(strlen(s) + 1);
  if (p != NULL) {
    strcpy(p, s);
  }
  return p;
}

struct tnode *treecpy(struct tnode *t, struct tnode *a) {
  if (t != NULL) {
    a = treecpy(t->left, a);
    a->word = t->word;
    a->count = t->count;
    ++a;
    a = treecpy(t->right, a);
  }
  return a;
}

int comp_tnode(const void *lhs, const void *rhs) {
  int x;
  int y;

  x = ((struct tnode *)lhs)->count;
  y = ((struct tnode *)rhs)->count;

  return (x > y) - (x < y);
}

int main() {
  struct tnode *root;
  char word[MAXWORD];
  int nc;
  struct tnode *arr;

  root = NULL;
  while (getword(word, MAXWORD) != EOF) {
    root = addtree(root, word, &nc);
  }
  arr = (struct tnode *)malloc(sizeof(struct tnode) * nc);
  treecpy(root, arr);
  qsort(arr, nc, sizeof(struct tnode), comp_tnode);
  while (nc-- > 0) {
    printf("%4d %s\n", arr[nc].count, arr[nc].word);
  }
  return 0;
}
