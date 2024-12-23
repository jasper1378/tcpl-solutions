#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101
#define MAXLINE 1024
#define MAXWORD 100

struct nlist {
  struct nlist *next;
  char *name;
  char *defn;
  int macro;
};

#define getch() getchar()
#define ungetch(c_) ungetc((c_), stdin)

char *strdup(const char *);
unsigned hash(const char *);
struct nlist *lookup(struct nlist *[HASHSIZE], const char *);
struct nlist *install(struct nlist *[HASHSIZE], const char *, const char *,
                      int);
void free_node(struct nlist *p);
void undef(struct nlist *[HASHSIZE], const char *);

const char *getword(const char *line, char *word, int size, int (*skip)(int),
                    int (*term)(int), void(skip_handler)(int));
/* I miss lambda... */
int char_true(int);
int char_false(int);
int char_newline(int);
int char_ident(int);
int char_not_ident(int);
void putchar_void(int);

int read_define(struct nlist *hashtab[HASHSIZE], const char *line);
int filter_code(struct nlist *hashtab[HASHSIZE], const char *line);

char *strdup(const char *s) {
  char *p;

  p = (char *)malloc(strlen(s) + 1);
  if (p != NULL) {
    strcpy(p, s);
  }
  return p;
}

unsigned hash(const char *s) {
  unsigned hashval;

  for (hashval = 0; *s != '\0'; ++s) {
    hashval = *s + 31 * hashval;
  }
  return hashval % HASHSIZE;
}

struct nlist *lookup(struct nlist *hashtab[HASHSIZE], const char *s) {
  struct nlist *np;
  unsigned hashval;

  hashval = hash(s);

  for (np = hashtab[hashval]; np != NULL; np = np->next) {
    if (strcmp(s, np->name) == 0) {
      return np;
    }
  }
  return NULL;
}

struct nlist *install(struct nlist *hashtab[HASHSIZE], const char *name,
                      const char *defn, int macro) {
  struct nlist *np;
  unsigned hashval;

  if ((np = lookup(hashtab, name)) == NULL) {
    np = (struct nlist *)malloc(sizeof(*np));
    if (np == NULL || (np->name = strdup(name)) == NULL) {
      return NULL;
    }
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  } else {
    free((void *)np->defn);
  }
  if ((np->defn = strdup(defn)) == NULL) {
    return NULL;
  }
  np->macro = macro;
  return np;
}

void free_node(struct nlist *p) {
  if (p != NULL) {
    free(p->name);
    free(p->defn);
    free(p);
  }
}

void undef(struct nlist *hashtab[HASHSIZE], const char *name) {

  unsigned hashval;
  struct nlist *head;
  struct nlist *np;

  hashval = hash(name);
  head = hashtab[hashval];

  if (head == NULL) {
    return;
  } else if (strcmp(head->name, name) == 0) {
    hashtab[hashval] = head->next;
    free_node(head);
    return;
  } else {
    for (np = head->next; np != NULL; head = np, np = np->next) {
      if (strcmp(np->name, name) == 0) {
        head->next = np->next;
        free_node(np);
        return;
      }
    }
  }
}

const char *getword(const char *line, char *word, int size, int (*skip)(int),
                    int (*term)(int), void(skip_handler)(int)) {

  int i;
  while (*line != '\0' && skip(*line)) {
    if (skip_handler) {
      skip_handler(*line);
    }
    ++line;
  }
  if (*line == '\0') {
    return NULL;
  }
  if (word == NULL) {
    return line;
  } else {
    for (i = 0; line[i] != '\0' && !term(line[i]) && i < (size - 1); ++i) {
      word[i] = line[i];
    }
    word[i] = '\0';
    return line + i;
  }
}

int char_true(int c) {
  (void)c;
  return 1;
}

int char_false(int c) {
  (void)c;
  return 0;
}

int char_newline(int c) { return c == '\n'; }

int char_ident(int c) { return isalnum(c) || c == '_'; }

int char_not_ident(int c) { return !char_ident(c); }

void putchar_void(int c) { putchar(c); }

int read_define(struct nlist *hashtab[HASHSIZE], const char *line) {
  char name[MAXWORD];
  char defn[MAXWORD];
  int macro;

  macro = 0;

  ++line;
  line = getword(line, name, MAXWORD, isspace, isspace, NULL);
  if (strcmp(name, "define") != 0) {
    return -1;
  }
  line = getword(line, name, MAXWORD, isspace, char_not_ident, NULL);
  if (line == NULL) {
    return -1;
  }
  if (*line == '(') {
    ++line;
    if (*line == ')') {
      ++line;
      macro = 1;
    } else {
      return -1;
    }
  }
  if (!isspace(*line)) {
    return -1;
  }
  line = getword(line, defn, MAXLINE, isspace, char_newline, NULL);
  if (line == NULL) {
    if (macro) {
      return -1;
    } else {
      install(hashtab, name, "1", 0);
      return 0;
    }
  } else {
    install(hashtab, name, defn, macro);
    return 0;
  }
}

int filter_code(struct nlist *hashtab[HASHSIZE], const char *line) {
  char word[MAXWORD];
  struct nlist *np;

  while ((line = getword(line, word, MAXWORD, char_not_ident, char_not_ident,
                         putchar_void)) != NULL) {
    np = lookup(hashtab, word);
    if (np == NULL) {
      fputs(word, stdout);
    } else {
      if (np->macro && (*line++ != '(' || *line++ != ')')) {
        return -1;
      }
      fputs(np->defn, stdout);
    }
  }
  return 0;
}

int main() {
  char line[MAXLINE];
  struct nlist *hashtab[HASHSIZE];
  const char *c;
  int i;
  struct nlist *p;
  struct nlist *t;
  int out;

  memset(hashtab, 0, HASHSIZE * sizeof(struct nlist *));
  out = EXIT_SUCCESS;

  while (fgets(line, MAXLINE, stdin) != NULL) {
    c = getword(line, NULL, 0, isspace, char_true, NULL);
    if (c == NULL) {
      fputs(line, stdout);
    } else if (*c == '#') {
      if (read_define(hashtab, c) != 0) {
        out = EXIT_FAILURE;
        break;
      }
    } else {
      if (filter_code((struct nlist **)hashtab, line) != 0) {
        out = EXIT_FAILURE;
        break;
      }
    }
  }
  for (i = 0; i < HASHSIZE; ++i) {
    for (p = hashtab[i]; p != NULL;) {
      t = p;
      p = p->next;
      free_node(t);
    }
  }
  return out;
}
