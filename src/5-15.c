#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALLOCSIZE 10000
#define MAXLEN 1000
#define MAXLINES 5000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;
char *lineptr[MAXLINES];

char *alloc(int);
void afree(char *);
int getline(char[], int);
int readlines(char *[], int);
void writelines(char *[], int);
void qsort_(void *[], int, int, int (*)(void *, void *), int);
int numcmp(char *, char *, int);
int strcmp_(char *, char *, int);
void swap(void *[], int, int);

enum {
  S_NONE = 0,
  S_NUMERIC,
  S_NOCASE,
};

int main(int argc, char *argv[]) {
  int nlines;
  int flags;
  int i;

  flags = S_NONE;

  for (i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "-n") == 0) {
      flags |= S_NUMERIC;
    } else if (strcmp(argv[i], "-f") == 0) {
      flags |= S_NOCASE;
    }
  }
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    qsort_((void **)lineptr, 0, nlines - 1,
           (int (*)(void *, void *))((flags & S_NUMERIC) ? numcmp : strcmp_),
           flags);
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

void qsort_(void *v[], int left, int right, int (*comp)(void *, void *),
            int flags) {
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
    c = (*comp)(v[i], v[left]);
    if (c < 0) {
      swap(v, ++last, i);
    }
  }
  swap(v, left, last);
  qsort_(v, left, last - 1, comp, flags);
  qsort_(v, last + 1, right, comp, flags);
}

int numcmp(char *s1, char *s2, int flags) {
  double v1;
  double v2;

  (void)flags;

  v1 = atof(s1);
  v2 = atof(s2);
  if (v1 < v2) {
    return -1;
  } else if (v1 > v2) {
    return 1;
  } else {
    return 0;
  }
}

int strcmp_(char *s1, char *s2, int flags) {
  (void)flags;

  for (; *s1 != '\0' && *s1 != '\0'; ++s1, ++s2) {
    if (((flags & S_NOCASE) && (tolower(*s1) != tolower(*s2))) ||
        (*s1 != *s2)) {
      break;
    }
  }
  if (flags & S_NOCASE) {
    return tolower(*s1) - tolower(*s2);
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
