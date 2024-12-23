#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101
#define MAXWORD 100

struct nlist {
  struct nlist *next;
  char *name;
  char *defn;
};

#define getch() getchar()
#define ungetch(c_) ungetc((c_), stdin)

char *strdup(char *);
int getword(char *, int);
unsigned hash(char *);
struct nlist *lookup(struct nlist *[HASHSIZE], char *);
struct nlist *install(struct nlist *[HASHSIZE], char *, char *);
void free_node(struct nlist *p);
void undef(struct nlist *[HASHSIZE], char *);
void print(struct nlist *[HASHSIZE]);

char *strdup(char *s) {
  char *p;

  p = (char *)malloc(strlen(s) + 1);
  if (p != NULL) {
    strcpy(p, s);
  }
  return p;
}

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

unsigned hash(char *s) {
  unsigned hashval;

  for (hashval = 0; *s != '\0'; ++s) {
    hashval = *s + 31 * hashval;
  }
  return hashval % HASHSIZE;
}

struct nlist *lookup(struct nlist *hashtab[HASHSIZE], char *s) {
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

struct nlist *install(struct nlist *hashtab[HASHSIZE], char *name, char *defn) {
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
  return np;
}

void free_node(struct nlist *p) {
  if (p != NULL) {
    free(p->name);
    free(p->defn);
    free(p);
  }
}

void undef(struct nlist *hashtab[HASHSIZE], char *name) {
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

void print(struct nlist *hashtab[HASHSIZE]) {
  unsigned i;
  struct nlist *p;
  for (i = 0; i < HASHSIZE; ++i) {
    if (hashtab[i] != NULL) {
      printf("%3u:\n", i);
      for (p = hashtab[i]; p != NULL; p = p->next) {
        printf("\t%s: %s\n", p->name, p->defn);
      }
    }
  }
}

int main() {
  struct nlist *hashtab[HASHSIZE];
  char cmd[MAXWORD];
  char name[MAXWORD];
  char defn[MAXWORD];
  unsigned i;
  struct nlist *p;
  struct nlist *temp;
  int out;

  out = EXIT_FAILURE;
  printf("usage:\n");
  printf("\tinstall <name> <defn>\n");
  printf("\tundef <name>\n");
  printf("\tprint\n");
  printf("\texit\n");
  while (getword(cmd, MAXWORD) != EOF) {
    if (strcmp(cmd, "install") == 0) {
      if (getword(name, MAXWORD) == EOF || getword(defn, MAXWORD) == EOF) {
        break;
      } else {
        install(hashtab, name, defn);
      }
    } else if (strcmp(cmd, "undef") == 0) {
      if (getword(name, MAXWORD) == EOF) {
        break;
      } else {
        undef(hashtab, name);
      }
    } else if (strcmp(cmd, "print") == 0) {
      print(hashtab);
    } else if (strcmp(cmd, "exit") == 0) {
      out = EXIT_SUCCESS;
      break;
    } else {
      break;
    }
  }
  for (i = 0; i < HASHSIZE; ++i) {
    for (p = hashtab[i]; p != NULL;) {
      temp = p;
      p = p->next;
      free_node(temp);
    }
  }
  return out;
}
