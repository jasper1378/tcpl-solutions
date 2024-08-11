#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 100

#define getch() getchar()
#define ungetch(c_) ungetc((c_), stdin)

enum { NAME, PARENS, BRACKETS };

int dcl(void);
int dirdcl(void);
int gettoken(void);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int main_dcl() {
  int c;

  while (gettoken() != EOF) {
    strcpy(datatype, token);
    out[0] = '\0';
    if (dcl() != 0 || tokentype != '\n') {
      printf("syntax error\n");
      out[0] = '\0';
      while ((c = getchar()) != '\n' && c != EOF)
        ;
    } else {
      printf("%s: %s %s\n", name, out, datatype);
    }
  }
  return 0;
}

int main_undcl() {
  int type;
  char temp[MAXTOKEN];

  while (gettoken() != EOF) {
    strcpy(out, token);
    while ((type = gettoken()) != '\n')
      if (type == PARENS || type == BRACKETS)
        strcat(out, token);
      else if (type == '*') {
        sprintf(temp, "(*%s)", out);
        strcpy(out, temp);
      } else if (type == NAME) {
        sprintf(temp, "%s %s", token, out);
        strcpy(out, temp);
      } else
        printf("invalid input at %s\n", token);
    printf("%s\n", out);
  }
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc > 1) {
    if (strcmp(argv[1], "d") == 0) {
      main_dcl();
    } else if (strcmp(argv[1], "u") == 0) {
      main_undcl();
    }
  }
}

int dcl(void) {
  int ns;

  for (ns = 0; gettoken() == '*';)
    ns++;
  if (dirdcl() != 0) {
    return -1;
  }
  while (ns-- > 0)
    strcat(out, " pointer to");
  return 0;
}

int dirdcl(void) {
  int type;

  if (tokentype == '(') {
    if (dcl() != 0) {
      return -1;
    }
    if (tokentype != ')') {
      printf("error: missing )\n");
      return -1;
    }
  } else if (tokentype == NAME)
    strcpy(name, token);
  else {
    printf("error: expected name or (dcl)\n");
    return -1;
  }
  while ((type = gettoken()) == PARENS || type == BRACKETS) {
    if (type == PARENS) {
      strcat(out, " function returning");
    } else {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
  }

  return 0;
}

int gettoken(void) {
  int c;
  char *p = token;

  while ((c = getch()) == ' ' || c == '\t')
    ;
  if (c == '(') {
    if ((c = getch()) == ')') {
      strcpy(token, "()");
      return tokentype = PARENS;
    } else {
      ungetch(c);
      return tokentype = '(';
    }
  } else if (c == '[') {
    for (*p++ = c; (*p++ = getch()) != ']';)
      ;
    *p = '\0';
    return tokentype = BRACKETS;
  } else if (isalpha(c)) {
    for (*p++ = c; isalnum(c = getch());) {
      *p++ = c;
    }
    *p = '\0';
    ungetch(c);
    return tokentype = NAME;
  } else {
    return tokentype = c;
  }
}
