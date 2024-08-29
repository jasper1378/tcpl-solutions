#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100

struct tnode {
  union {
    struct {
      char *prefix;
      struct tnode *words;
    } group;
    struct {
      char *word;
      int count;
    } member;
  } u;
  struct tnode *left;
  struct tnode *right;
};

int getword(char *word, int lim);
struct tnode *addtree(struct tnode *, char *, int n);
void treeprint(struct tnode *, char t);
struct tnode *talloc(void);
char *strdup(char *);
char *strndup(char *, int);

struct tnode *addtree(struct tnode *p, char *w, int n) {
  int cond;

  cond = 0;

  if (n < 0 && p == NULL) {
    p = talloc();
    p->u.member.word = strdup(w);
    p->u.member.count = 1;
    p->left = p->right = NULL;
  } else if (n > 0 && p == NULL) {
    p = talloc();
    p->u.group.prefix = strndup(w, n);
    p->u.group.words = NULL;
    p->u.group.words = addtree(p->u.group.words, w, -1);
    p->left = p->right = NULL;
  } else if (n < 0 && (cond = strcmp(w, p->u.member.word)) == 0) {
    p->u.member.count++;
  } else if (n > 0 && (cond = strncmp(w, p->u.group.prefix, n)) == 0) {
    p->u.group.words = addtree(p->u.group.words, w, -1);
  } else if (cond < 0) {
    p->left = addtree(p->left, w, n);
  } else if (cond > 0) {
    p->right = addtree(p->right, w, n);
  }

  return p;
}

void treeprint(struct tnode *p, char t) {
  if (p != NULL) {
    treeprint(p->left, t);
    if (t == 'g') {
      printf("group \"%s\":\n", p->u.group.prefix);
      treeprint(p->u.group.words, 'm');
      putchar('\n');
    } else if (t == 'm') {
      printf("%4d %s\n", p->u.member.count, p->u.member.word);
    }
    treeprint(p->right, t);
  }
}

int main(int argc, char *argv[]) {
  struct tnode *root;
  char word[MAXWORD];
  int n;

  if (argc == 1) {
    n = 6;
  } else if (argc == 2) {
    n = atoi(argv[1]);
    if (n <= 0) {
      return -1;
    }
  } else {
    return -1;
  }

  root = NULL;
  while (getword(word, MAXWORD) != EOF) {
    if (isalpha(word[0])) {
      root = addtree(root, word, n);
    }
  }
  treeprint(root, 'g');
  return 0;
}
