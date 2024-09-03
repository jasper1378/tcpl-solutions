#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100

#define getch() getchar()
#define ungetch(c_) ungetc((c_), stdin)

struct tnode {
  union {
    struct {
      char *word;
      struct tnode *lines;
    } word;
    struct {
      int line;
      int count;
    } line;
  } u;
  struct tnode *left;
  struct tnode *right;
};

int getword(char *, int);
struct tnode *addtree(struct tnode *, char *, int, char);
void treeprint(struct tnode *, char);
int noiseword(char *);
char *binsearch(char *, char **, int);
struct tnode *talloc(void);
char *strdup(char *s);

char *binsearch(char *word, char **tab, int n) {
  int cond;
  char **low = &tab[0];
  char **high = &tab[n];
  char **mid;

  while (low < high) {
    mid = low + (high - low) / 2;
    if ((cond = strcmp(word, *mid)) < 0) {
      high = mid;
    } else if (cond > 0) {
      low = mid + 1;
    } else {
      return *mid;
    }
  }
  return NULL;
}

struct tnode *talloc(void) {
  return (struct tnode *)malloc(sizeof(struct tnode));
}

char *strdup(char *s) {
  char *p;

  p = (char *)malloc(strlen(s) + 1);
  if (p != NULL)
    strcpy(p, s);
  return p;
}

int linenum = 1;
#define NOISEWORDS_LEN 2
char *noisewords[] = {"the", "and"};

int getword(char *word, int lim) {
  int c;
  char *w;

  w = word;

  while (isspace(c = getch())) {
    if (c == '\n') {
      ++linenum;
    }
  }
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

struct tnode *addtree(struct tnode *p, char *w, int l, char t) {
  int cond;

  cond = 0;

  if (!noiseword(w)) {
    if (t == 'w' && p == NULL) {
      p = talloc();
      p->u.word.word = strdup(w);
      p->u.word.lines = NULL;
      p->u.word.lines = addtree(p->u.word.lines, w, l, 'l');
      p->left = p->right = NULL;
    } else if (t == 'l' && p == NULL) {
      p = talloc();
      p->u.line.line = l;
      p->u.line.count = 1;
      p->left = p->right = NULL;
    } else if (t == 'w' && (cond = strcmp(w, p->u.word.word)) == 0) {
      p->u.word.lines = addtree(p->u.word.lines, w, l, 'l');
    } else if (t == 'l' && l == p->u.line.line) {
      ++p->u.line.count;
    } else if (cond < 0) {
      p->left = addtree(p->left, w, l, t);
    } else {
      p->right = addtree(p->right, w, l, t);
    }
  }
  return p;
}

void treeprint(struct tnode *p, char t) {
  if (p != NULL) {
    treeprint(p->left, t);
    if (t == 'w') {
      printf("\"%s\"\n", p->u.word.word);
      treeprint(p->u.word.lines, 'l');
      putchar('\n');
    } else if (t == 'l') {
      printf("%d\n", p->u.line.line);
    }
    treeprint(p->right, t);
  }
}

int noiseword(char *w) {
  return binsearch(w, noisewords, NOISEWORDS_LEN) != NULL;
}

int main() {
  struct tnode *root;
  char word[MAXWORD];

  root = NULL;

  while (getword(word, MAXWORD) != EOF) {
    root = addtree(root, word, linenum, 'w');
  }
  treeprint(root, 'w');
  return 0;
}
