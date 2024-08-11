#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALLOCSIZE 10000
#define MAXLEN 1000
#define MAXLINES 5000
#define MAXFIELDS 100

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;
char *lineptr[MAXLINES];

char *alloc(int);
void afree(char *);
int getline(char[], int);
int readlines(char *[], int);
void writelines(char *[], int);
void qsort_(void *[], int, int, int (*)(void *, void *, int, int[MAXFIELDS]),
            int, int[MAXFIELDS]);
int cmp(char *, char *, int, int[MAXFIELDS]);
int numcmp(char *, int, char *, int, int);
int strcmp_(char *, int, char *, int, int);
void swap(void *[], int, int);

enum {
  S_NONE = 0,
  S_NUMERIC = 1 << 0,
};

int main(int argc, char *argv[]) {
  int nlines;
  int flags;
  int fflags[MAXFIELDS];
  int i;

  flags = S_NONE;

  for (i = 1; i < argc; ++i) {
    if (strncmp(argv[i], "-n", strlen("-n")) == 0) {
      if (isdigit(argv[i][strlen("-n")])) {
        fflags[atoi(&argv[i][strlen("-n")])] |= S_NUMERIC;
      } else {
        flags |= S_NUMERIC;
      }
    }
  }
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    qsort_((void **)lineptr, 0, nlines - 1,
           (int (*)(void *, void *, int, int[MAXFIELDS]))(cmp), flags, fflags);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("input too big to sort\n");
    return 1;
  }
}

char *alloc(int n) {
  if (allocbuf + ALLOCSIZE - allocp >= n) {
    allocp += n;
    return allocp - n;
  } else {
    return 0;
  }
}

void afree(char *p) {
  if (p >= allocbuf && p < allocbuf + ALLOCSIZE) {
    allocp = p;
  }
}

int getline(char s[], int lim) {
  int c;
  int i;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
    s[i] = c;
  }
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return i;
}

int readlines(char *lineptr[], int maxlines) {
  int len;
  int nlines;
  char *p;
  char line[MAXLEN];

  nlines = 0;
  while ((len = getline(line, MAXLEN)) > 0) {
    if (nlines >= maxlines || (p = alloc(len)) == NULL)
      return -1;
    else {
      line[len - 1] = '\0';
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  }
  return nlines;
}

void writelines(char *lineptr[], int nlines) {
  int i;

  for (i = 0; i < nlines; i++) {
    printf("%s\n", lineptr[i]);
  }
}

void qsort_(void *v[], int left, int right,
            int (*comp)(void *, void *, int, int[MAXFIELDS]), int flags,
            int fflags[MAXFIELDS]) {
  int i;
  int last;
  int c;

  void swap(void *v[], int, int);

  if (left >= right) {
    return;
  }
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++) {
    c = (*comp)(v[i], v[left], flags, fflags);
    if (c < 0) {
      swap(v, ++last, i);
    }
  }
  swap(v, left, last);
  qsort_(v, left, last - 1, comp, flags, fflags);
  qsort_(v, last + 1, right, comp, flags, fflags);
}

int cmp(char *s1, char *s2, int flags, int fflags[MAXFIELDS]) {
  int i;
  int j;
  int f;
  int r;

  f = 0;

  for (;;) {
    for (i = 0; s1[i] != '\0' && s1[i] != '\t'; ++i)
      ;
    for (j = 0; s2[j] != '\0' && s2[j] != '\t'; ++j)
      ;
    if (flags & S_NUMERIC || fflags[f] & S_NUMERIC) {
      r = numcmp(s1, i, s2, j, flags);
    } else {
      r = strcmp_(s1, i, s2, j, flags);
    }
    if (r != 0) {
      return r;
    }
    s1 += i;
    s2 += j;
    ++f;

    for (; *s1 == '\t'; ++s1)
      ;
    for (; *s2 == '\t'; ++s2)
      ;
    if (*s1 == '\0' || *s2 == '\0') {
      return 0;
    }
  }
}

int numcmp(char *s1, int l1, char *s2, int l2, int flags) {
  double v1;
  double v2;
  char *s11;
  char *s21;

  s11 = alloc(l1 + 1);
  s21 = alloc(l2 + 1);
  strncpy(s11, s1, l1 + 1);
  strncpy(s21, s2, l2 + 1);

  (void)flags;

  v1 = atof(s11);
  v2 = atof(s21);

  afree(s21);
  afree(s11);

  if (v1 < v2) {
    return -1;
  } else if (v1 > v2) {
    return 1;
  } else {
    return 0;
  }
}

int strcmp_(char *s1, int l1, char *s2, int l2, int flags) {
  int i;

  (void)flags;

  for (i = 0; i < l1 && i < l2 && *s1 != '\0' && *s1 != '\0'; ++i, ++s1, ++s2) {
    if (*s1 != *s2) {
      break;
    }
  }

  if ((i == l1 && i == l2) || (*s1 == '\0' && *s2 == '\0')) {
    return 0;
  } else if (i == l1 || *s1 == '\0') {
    return -1;
  } else if (i == l2 || *s2 == '\0') {
    return 1;
  } else {
    return *s1 - *s2;
  }
}

void swap(void *v[], int i, int j) {
  void *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
