#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_STR 100
#define MAX_FPAR 100

enum e_prog { E_PROG_DCL, E_PROG_UNDCL };

typedef enum e_bool { FALSE = 0, TRUE = 1 } bool_t;

enum e_return { E_RETURN_ERROR = -1, E_RETURN_FALSE = 0, E_RETURN_TRUE = 1 };

enum e_lang { E_LANG_C, E_LANG_ENG };

enum e_cv { E_CV_NONE = 0, E_CV_CONST = 1 << 0, E_CV_VOLATILE = 1 << 1 };

enum e_sign { E_SIGN_NONE, E_SIGN_SIGNED, E_SIGN_UNSIGNED };

enum e_type { E_TYPE_VOID = 1, E_TYPE_BASIC, E_TYPE_ENUM, E_TYPE_DERIV };

enum e_type_basic { E_TYPE_BASIC_INT = 1, E_TYPE_BASIC_FLOAT };

enum e_type_basic_int {
  E_TYPE_BASIC_INT_CHAR = 1,
  E_TYPE_BASIC_INT_SHORT,
  E_TYPE_BASIC_INT_INT,
  E_TYPE_BASIC_INT_LONG
};

enum e_type_basic_float {
  E_TYPE_BASIC_FLOAT_FLOAT = 1,
  E_TYPE_BASIC_FLOAT_DOUBLE,
  E_TYPE_BASIC_FLOAT_LDOUBLE
};

enum e_type_deriv {
  E_TYPE_DERIV_ARRAY = 1,
  E_TYPE_DERIV_STRUCT,
  E_TYPE_DERIV_UNION,
  E_TYPE_DERIV_FUNC,
  E_TYPE_DERIV_PTR
};

enum e_type_abs {
  E_TYPE_ABS_VOID = 1,
  E_TYPE_ABS_CHAR,
  E_TYPE_ABS_SHORT,
  E_TYPE_ABS_INT,
  E_TYPE_ABS_LONG,
  E_TYPE_ABS_FLOAT,
  E_TYPE_ABS_DOUBLE,
  E_TYPE_ABS_LDOUBLE,
  E_TYPE_ABS_ENUM,
  E_TYPE_ABS_ARRAY,
  E_TYPE_ABS_STRUCT,
  E_TYPE_ABS_UNION,
  E_TYPE_ABS_FUNC,
  E_TYPE_ABS_PTR
};

enum e_keyword {
  E_KEYWORD_CHAR = 1,
  E_KEYWORD_CONST,
  E_KEYWORD_DOUBLE,
  E_KEYWORD_ENUM,
  E_KEYWORD_FLOAT,
  E_KEYWORD_INT,
  E_KEYWORD_LDOUBLE,
  E_KEYWORD_LONG,
  E_KEYWORD_SHORT,
  E_KEYWORD_SIGNED,
  E_KEYWORD_STRUCT,
  E_KEYWORD_UNION,
  E_KEYWORD_UNSIGNED,
  E_KEYWORD_VOID,
  E_KEYWORD_VOLATILE
};

enum e_token {
  E_TOKEN_PTR = 1,
  E_TOKEN_COMMA,
  E_TOKEN_SEMICOLON,
  E_TOKEN_ARRAY,
  E_TOKEN_OPAREN,
  E_TOKEN_CPAREN,
  E_TOKEN_NAME,
  E_TOKEN_KEYWORD
};

enum e_move { E_MOVE_RIGHT = 1, E_MOVE_LEFT };

struct declaration {
  char *name;
  struct type *type;
};

struct type {
  enum e_type_abs type_abs;
  enum e_type type;
  union {
    struct type_void *type_void;
    struct type_basic *type_basic;
    struct type_enum *type_enum;
    struct type_deriv *type_deriv;
  } type_u;
  enum e_cv cv;
};

struct type_void {
  char avoid_empty_struct_warning;
};

struct type_basic {
  enum e_type_basic type_basic;
  union {
    struct type_basic_int *type_basic_int;
    struct type_basic_float *type_basic_float;
  } type_basic_u;
};

struct type_basic_int {
  enum e_type_basic_int type_basic_int;
  enum e_sign sign;
};

struct type_basic_float {
  enum e_type_basic_float type_basic_float;
};

struct type_enum {
  char *name;
};

struct type_deriv {
  enum e_type_deriv type_deriv;
  union {
    struct type_deriv_array *type_deriv_array;
    struct type_deriv_struct *type_deriv_struct;
    struct type_deriv_union *type_deriv_union;
    struct type_deriv_func *type_deriv_func;
    struct type_deriv_ptr *type_deriv_ptr;
  } type_deriv_u;
};

struct type_deriv_array {
  struct type *type;
  size_t size;
};

struct type_deriv_struct {
  char *name;
};

struct type_deriv_union {
  char *name;
};

struct type_deriv_func {
  struct type *type_ret;
  struct type **type_params;
  size_t type_params_len;
};

struct type_deriv_ptr {
  struct type *type;
};

struct token {
  enum e_token token;
  union {
    char *name;
    struct {
      enum e_keyword keyword;
      union {
        char *name;
      } value;
    } keyword;
    size_t arrsize;
  } value;
};

#define salloc(struct_) (struct_ *)calloc(1, sizeof(struct_));
size_t strnlen(const char *s, size_t n);
char *strndup(const char *s, size_t n);
char *strdup(const char *s);

#define GENERATE_FREE_STRUCT_FUNC(name_)                                       \
  void free_##name_(struct name_ *ptr) {                                       \
    if (ptr) {                                                                 \
      dtor_##name_(ptr);                                                       \
      free(ptr);                                                               \
    }                                                                          \
  }

void dtor_declaration(struct declaration *ptr);
GENERATE_FREE_STRUCT_FUNC(declaration)
void dtor_type(struct type *ptr);
GENERATE_FREE_STRUCT_FUNC(type)
void dtor_type_void(struct type_void *ptr);
GENERATE_FREE_STRUCT_FUNC(type_void)
void dtor_type_basic(struct type_basic *ptr);
GENERATE_FREE_STRUCT_FUNC(type_basic)
void dtor_type_basic_int(struct type_basic_int *ptr);
GENERATE_FREE_STRUCT_FUNC(type_basic_int)
void dtor_type_basic_float(struct type_basic_float *ptr);
GENERATE_FREE_STRUCT_FUNC(type_basic_float)
void dtor_type_enum(struct type_enum *ptr);
GENERATE_FREE_STRUCT_FUNC(type_enum)
void dtor_type_deriv(struct type_deriv *ptr);
GENERATE_FREE_STRUCT_FUNC(type_deriv)
void dtor_type_deriv_array(struct type_deriv_array *ptr);
GENERATE_FREE_STRUCT_FUNC(type_deriv_array)
void dtor_type_deriv_struct(struct type_deriv_struct *ptr);
GENERATE_FREE_STRUCT_FUNC(type_deriv_struct)
void dtor_type_deriv_union(struct type_deriv_union *ptr);
GENERATE_FREE_STRUCT_FUNC(type_deriv_union)
void dtor_type_deriv_func(struct type_deriv_func *ptr);
GENERATE_FREE_STRUCT_FUNC(type_deriv_func)
void dtor_type_deriv_ptr(struct type_deriv_ptr *ptr);
GENERATE_FREE_STRUCT_FUNC(type_deriv_ptr)
void dtor_token(struct token *ptr);
GENERATE_FREE_STRUCT_FUNC(token)

enum e_return lex(enum e_lang lang, const char *str, struct token *tokens,
                  size_t *size);
enum e_return lex_read_name(enum e_lang lang, const char *str, size_t *is,
                            char *buf, size_t *ib);
void lex_skip_whitespace(enum e_lang lang, const char *str, size_t *is);

enum e_return parse(enum e_lang lang, const struct token *tokens, size_t size,
                    struct declaration *decl);
enum e_return parse_decl(enum e_lang lang, const struct token *tokens,
                         size_t size, struct declaration *decl);
enum e_return parse_type(enum e_lang lang, const struct token *tokens,
                         size_t size, size_t *ic, size_t *il, size_t *ir,
                         struct type *type);
enum e_return parse_seek_start(enum e_lang lang, const struct token *tokens,
                               size_t size, bool_t declaration, size_t *ic);
enum e_return parse_next_token(enum e_lang lang, const struct token *tokens,
                               size_t size, size_t *ic, size_t *il, size_t *ir,
                               enum e_move move);
enum e_return parse_next_fpar(enum e_lang lang, const struct token *tokens,
                              size_t size, size_t *ic, size_t *il, size_t *ir,
                              const struct token **ptokens, size_t *psize);

void serialize(enum e_lang lang, const struct declaration *decl);
void serialize_decl(enum e_lang lang, const struct declaration *decl,
                    char *str);
void serialize_type(enum e_lang lang, const struct type *type, char *str);

int str_to_keyword(const char *str);
int keyword_to_enum(enum e_keyword keyword, bool_t abs);
const char *cv_to_str(enum e_cv cv, int space);
const char *type_to_str(enum e_type_abs type);

size_t strnlen(const char *s, size_t n) {
  size_t i;

  for (i = 0; i < n; ++i) {
    if (s[i] == '\0') {
      break;
    }
  }
  return i;
}

char *strdup(const char *s) {
  size_t len;
  char *result;

  len = strlen(s) + 1;
  result = malloc(len);
  if (result == NULL) {
    return NULL;
  }
  return memcpy(result, s, len);
}

char *strndup(const char *s, size_t n) {
  char *result;
  size_t len;

  len = strnlen(s, n);
  result = malloc(len + 1);
  if (result == NULL) {
    return NULL;
  }
  result[len] = '\0';
  return memcpy(result, s, len);
}

void dtor_declaration(struct declaration *ptr) {
  free(ptr->name);
  free_type(ptr->type);
}

void dtor_type(struct type *ptr) {
  switch (ptr->type) {
  case E_TYPE_VOID:
    free_type_void(ptr->type_u.type_void);
    break;
  case E_TYPE_BASIC:
    free_type_basic(ptr->type_u.type_basic);
    break;
  case E_TYPE_ENUM:
    free_type_enum(ptr->type_u.type_enum);
    break;
  case E_TYPE_DERIV:
    free_type_deriv(ptr->type_u.type_deriv);
    break;
  }
}

void dtor_type_void(struct type_void *ptr) { (void)ptr; }

void dtor_type_basic(struct type_basic *ptr) {
  switch (ptr->type_basic) {
  case E_TYPE_BASIC_INT:
    free_type_basic_int(ptr->type_basic_u.type_basic_int);
    break;
  case E_TYPE_BASIC_FLOAT:
    free_type_basic_float(ptr->type_basic_u.type_basic_float);
    break;
  }
}

void dtor_type_basic_int(struct type_basic_int *ptr) { (void)ptr; }

void dtor_type_basic_float(struct type_basic_float *ptr) { (void)ptr; }

void dtor_type_enum(struct type_enum *ptr) { free(ptr->name); }

void dtor_type_deriv(struct type_deriv *ptr) {
  switch (ptr->type_deriv) {
  case E_TYPE_DERIV_ARRAY:
    free_type_deriv_array(ptr->type_deriv_u.type_deriv_array);
    break;
  case E_TYPE_DERIV_STRUCT:
    free_type_deriv_struct(ptr->type_deriv_u.type_deriv_struct);
    break;
  case E_TYPE_DERIV_UNION:
    free_type_deriv_union(ptr->type_deriv_u.type_deriv_union);
    break;
  case E_TYPE_DERIV_FUNC:
    free_type_deriv_func(ptr->type_deriv_u.type_deriv_func);
    break;
  case E_TYPE_DERIV_PTR:
    free_type_deriv_ptr(ptr->type_deriv_u.type_deriv_ptr);
    break;
  }
}

void dtor_type_deriv_array(struct type_deriv_array *ptr) {
  free_type(ptr->type);
}

void dtor_type_deriv_struct(struct type_deriv_struct *ptr) { free(ptr->name); }

void dtor_type_deriv_union(struct type_deriv_union *ptr) { free(ptr->name); }

void dtor_type_deriv_func(struct type_deriv_func *ptr) {
  size_t i;

  free_type(ptr->type_ret);
  for (i = 0; i < ptr->type_params_len; ++i) {
    free_type(ptr->type_params[i]);
  }
  free(ptr->type_params);
}

void dtor_type_deriv_ptr(struct type_deriv_ptr *ptr) { free_type(ptr->type); }

void dtor_token(struct token *ptr) {
  if (ptr->token == E_TOKEN_NAME) {
    free(ptr->value.name);
  } else if (ptr->token == E_TOKEN_KEYWORD) {
    switch (ptr->value.keyword.keyword) {
    case E_KEYWORD_ENUM:
    case E_KEYWORD_STRUCT:
    case E_KEYWORD_UNION: {
      free(ptr->value.keyword.value.name);
    } break;
    default:
      break;
    }
  }
}

enum e_return lex(enum e_lang lang, const char *str, struct token *tokens,
                  size_t *size) {
  enum e_return ret;
  size_t is;
  size_t isp;
  size_t it;
  char buf[MAX_STR];
  size_t ib;
  long parens;
  int keyw;

  ret = E_RETURN_ERROR;
  ib = 0;
  parens = 0;

  for (is = 0, it = 0; str[is] != '\0' && it < *size; ++is) {
    switch (str[is]) {
    case ' ':
    case '\t': {
      continue;
    } break;
    case '\n': {
      ret = E_RETURN_ERROR;
      goto out;
    } break;
    case '*': {
      tokens[it++].token = E_TOKEN_PTR;
    } break;
    case ',': {
      tokens[it++].token = E_TOKEN_COMMA;
    } break;
    case ';': {
      tokens[it++].token = E_TOKEN_SEMICOLON;
      ret = E_RETURN_TRUE;
      goto out;
    } break;
    case '[': {
      ++is;
      lex_skip_whitespace(lang, str, &is);
      for (ib = 0; ib < (MAX_STR - 1) && isdigit(str[is]); ++ib, ++is) {
        buf[ib] = str[is];
      }
      buf[ib] = '\0';
      lex_skip_whitespace(lang, str, &is);
      if (str[is] != ']') {
        ret = E_RETURN_ERROR;
        goto out;
      }
      tokens[it].token = E_TOKEN_ARRAY;
      tokens[it].value.arrsize = (size_t)strtoul(buf, NULL, 10);
      ++it;
    } break;
    case ']': {
      ret = E_RETURN_ERROR;
      goto out;
    } break;
    case '(': {
      tokens[it++].token = E_TOKEN_OPAREN;
      ++parens;
    } break;
    case ')': {
      tokens[it++].token = E_TOKEN_CPAREN;
      --parens;
    } break;
    default: {
      if ((ret = lex_read_name(lang, str, &is, buf, &ib)) == E_RETURN_ERROR) {
        goto out;
      }
      if ((keyw = str_to_keyword(buf)) != -1) {
        tokens[it].token = E_TOKEN_KEYWORD;
        tokens[it].value.keyword.keyword = (enum e_keyword)keyw;
        switch (keyw) {
        case E_KEYWORD_ENUM:
        case E_KEYWORD_STRUCT:
        case E_KEYWORD_UNION: {
          ++is;
          lex_skip_whitespace(lang, str, &is);
          if ((ret = lex_read_name(lang, str, &is, buf, &ib)) ==
              E_RETURN_ERROR) {
            goto out;
          }
          tokens[it].value.keyword.value.name = strndup(buf, ib);
        } break;
        case E_KEYWORD_LONG: {
          isp = is;
          ++isp;
          lex_skip_whitespace(lang, str, &isp);
          if (lex_read_name(lang, str, &isp, buf, &ib) == E_RETURN_TRUE) {
            if ((keyw = str_to_keyword(buf)) == E_KEYWORD_DOUBLE) {
              tokens[it].value.keyword.keyword = E_KEYWORD_LDOUBLE;
              is = isp;
            }
          }
        } break;
        default:
          break;
        }
      } else {
        tokens[it].token = E_TOKEN_NAME;
        tokens[it].value.name = strndup(buf, ib);
      }
      ++it;
    } break;
    }
  }

out:;

  if (parens != 0) {
    ret = E_RETURN_ERROR;
  }

  *size = it;

  return ret;
}

enum e_return lex_read_name(enum e_lang lang, const char *str, size_t *is,
                            char *buf, size_t *ib) {
  (void)lang;

  for (*ib = 0; *ib < (MAX_STR - 1) && (isalnum(str[*is]) || str[*is] == '_');
       ++*ib, ++*is) {
    buf[*ib] = str[*is];
  }
  buf[*ib] = '\0';
  --*is;
  if (buf[0] == '\0') {
    return E_RETURN_ERROR;
  } else {
    return E_RETURN_TRUE;
  }
}

void lex_skip_whitespace(enum e_lang lang, const char *str, size_t *is) {
  (void)lang;

  for (; str[*is] == ' ' || str[*is] == '\t'; ++*is)
    ;
}

enum e_return parse(enum e_lang lang, const struct token *tokens, size_t size,
                    struct declaration *decl) {
  return parse_decl(lang, tokens, size, decl);
}

enum e_return parse_decl(enum e_lang lang, const struct token *tokens,
                         size_t size, struct declaration *decl) {
  size_t ic;
  size_t il;
  size_t ir;

  ic = il = ir = 0;

  if (parse_seek_start(lang, tokens, size, TRUE, &ic) == E_RETURN_ERROR) {
    return E_RETURN_ERROR;
  }
  il = ir = ic;

  decl->name = strdup(tokens[ic].value.name);

  if (parse_next_token(lang, tokens, size, &ic, &il, &ir, E_MOVE_RIGHT) ==
      E_RETURN_FALSE) {
    return E_RETURN_ERROR;
  }

  decl->type = salloc(struct type);

  return parse_type(lang, tokens, size, &ic, &il, &ir, decl->type);
}

enum e_return parse_type(enum e_lang lang, const struct token *tokens,
                         size_t size, size_t *ic, size_t *il, size_t *ir,
                         struct type *type) {
  enum e_return ret;
  struct type **head;
  struct type **prev;
  long parens;
  enum e_sign csign;
  enum e_cv cv;
  enum e_sign sign;
  bool_t eint;
  enum e_keyword keyw;
  const struct token *ptokens;
  size_t psize;
  size_t icp;
  size_t ilp;
  size_t irp;
  size_t i;

  ret = E_RETURN_TRUE;
  prev = head = &type;
  parens = 0;
  csign = E_SIGN_NONE;
  eint = FALSE;

  while (ret == E_RETURN_TRUE) {
    switch (tokens[*ic].token) {
    case E_TOKEN_PTR: {
      if (!head) {
        ret = E_RETURN_ERROR;
        goto out;
      }
      if (lang == E_LANG_C && *ic != *il) {
        ret = E_RETURN_ERROR;
        goto out;
      }
      if (csign != E_SIGN_NONE) {
        ret = E_RETURN_ERROR;
        goto out;
      }
      (*head)->type_abs = E_TYPE_ABS_PTR;
      (*head)->type = E_TYPE_DERIV;
      (*head)->type_u.type_deriv = salloc(struct type_deriv);
      (*head)->type_u.type_deriv->type_deriv = E_TYPE_DERIV_PTR;
      (*head)->type_u.type_deriv->type_deriv_u.type_deriv_ptr =
          salloc(struct type_deriv_ptr);
      prev = head;
      head = &((*head)->type_u.type_deriv->type_deriv_u.type_deriv_ptr->type);
      (*head) = salloc(struct type);

      ret = parse_next_token(lang, tokens, size, ic, il, ir,
                             (lang == E_LANG_C) ? E_MOVE_LEFT : E_MOVE_RIGHT);
    } break;
    case E_TOKEN_COMMA: {
      ret = E_RETURN_ERROR;
      goto out;
    } break;
    case E_TOKEN_SEMICOLON: {
      ret = parse_next_token(lang, tokens, size, ic, il, ir,
                             (lang == E_LANG_C) ? E_MOVE_LEFT : E_MOVE_RIGHT);
    } break;
    case E_TOKEN_ARRAY: {
      if (!head) {
        ret = E_RETURN_ERROR;
        goto out;
      }
      if (lang == E_LANG_C && *ic != *ir) {
        ret = E_RETURN_ERROR;
        goto out;
      }
      if ((*head)->cv != E_CV_NONE || csign != E_SIGN_NONE) {
        ret = E_RETURN_ERROR;
        goto out;
      }
      (*head)->type_abs = E_TYPE_ABS_ARRAY;
      (*head)->type = E_TYPE_DERIV;
      (*head)->type_u.type_deriv = salloc(struct type_deriv);
      (*head)->type_u.type_deriv->type_deriv = E_TYPE_DERIV_ARRAY;
      (*head)->type_u.type_deriv->type_deriv_u.type_deriv_array =
          salloc(struct type_deriv_array);
      (*head)->type_u.type_deriv->type_deriv_u.type_deriv_array->size =
          tokens[*ic].value.arrsize;
      prev = head;
      head = &((*head)->type_u.type_deriv->type_deriv_u.type_deriv_array->type);
      (*head) = salloc(struct type);

      ret = parse_next_token(lang, tokens, size, ic, il, ir, E_MOVE_RIGHT);
    } break;
    case E_TOKEN_OPAREN: {
      if (lang == E_LANG_C && *ic == *il) {
        ++parens;
        ret = parse_next_token(lang, tokens, size, ic, il, ir, E_MOVE_RIGHT);
      } else {
        if (!head) {
          ret = E_RETURN_ERROR;
          goto out;
        }
        if ((*head)->cv != E_CV_NONE || csign != E_SIGN_NONE) {
          ret = E_RETURN_ERROR;
          goto out;
        }
        (*head)->type_abs = E_TYPE_ABS_FUNC;
        (*head)->type = E_TYPE_DERIV;
        (*head)->type_u.type_deriv = salloc(struct type_deriv);
        (*head)->type_u.type_deriv->type_deriv = E_TYPE_DERIV_FUNC;
        (*head)->type_u.type_deriv->type_deriv_u.type_deriv_func =
            salloc(struct type_deriv_func);
        (*head)->type_u.type_deriv->type_deriv_u.type_deriv_func->type_params =
            calloc(MAX_FPAR, sizeof(struct type *));

        for (psize = 0, i = 0;
             (ret = parse_next_fpar(lang, tokens, size, ic, il, ir, &ptokens,
                                    &psize)) == E_RETURN_TRUE;
             ++i) {
          if (psize == 0) {
            break;
          } else {
            icp = ilp = irp = 0;
            if (parse_seek_start(lang, ptokens, psize, FALSE, &icp) ==
                E_RETURN_ERROR) {
              ret = E_RETURN_ERROR;
              goto out;
            }
            ilp = irp = icp;

            (*head)
                ->type_u.type_deriv->type_deriv_u.type_deriv_func
                ->type_params[i] = salloc(struct type);
            if (parse_type(lang, ptokens, psize, &icp, &ilp, &irp,
                           (*head)
                               ->type_u.type_deriv->type_deriv_u
                               .type_deriv_func->type_params[i]) ==
                E_RETURN_ERROR) {
              ret = E_RETURN_ERROR;
              goto out;
            }
          }
        }

        if (ret == E_RETURN_ERROR) {
          goto out;
        }

        (*head)
            ->type_u.type_deriv->type_deriv_u.type_deriv_func->type_params_len =
            i;
        (*head)->type_u.type_deriv->type_deriv_u.type_deriv_func->type_params =
            realloc((*head)
                        ->type_u.type_deriv->type_deriv_u.type_deriv_func
                        ->type_params,
                    (((*head)
                          ->type_u.type_deriv->type_deriv_u.type_deriv_func
                          ->type_params_len) *
                     sizeof(struct type *)));

        prev = head;
        head = &(
            (*head)->type_u.type_deriv->type_deriv_u.type_deriv_func->type_ret);
        (*head) = salloc(struct type);

        ret = parse_next_token(lang, tokens, size, ic, il, ir, E_MOVE_RIGHT);
      }
    } break;
    case E_TOKEN_CPAREN: {
      if (lang == E_LANG_ENG || *ic == *il) {
        ret = E_RETURN_ERROR;
        goto out;
      } else if (*ic == *ir) {
        --parens;
        ret = parse_next_token(lang, tokens, size, ic, il, ir, E_MOVE_LEFT);
      }
    } break;
    case E_TOKEN_NAME: {
      ret = E_RETURN_ERROR;
      goto out;
    } break;
    case E_TOKEN_KEYWORD: {
      if (lang == E_LANG_C && *ic != *il) {
        ret = E_RETURN_ERROR;
        goto out;
      }
      switch (keyw = tokens[*ic].value.keyword.keyword) {
      case E_KEYWORD_CHAR:
      case E_KEYWORD_INT:
      case E_KEYWORD_LONG:
      case E_KEYWORD_SHORT: {
        if (keyw == E_KEYWORD_INT && !eint &&
            ((*prev)->type_abs == E_TYPE_ABS_LONG ||
             (*prev)->type_abs == E_TYPE_ABS_SHORT)) {
          eint = TRUE;
        } else if ((keyw == E_KEYWORD_LONG || keyw == E_KEYWORD_SHORT) &&
                   (*prev)->type_abs == E_TYPE_ABS_INT) {
          (*prev)->type_abs = keyword_to_enum(keyw, TRUE);
          (*prev)
              ->type_u.type_basic->type_basic_u.type_basic_int->type_basic_int =
              keyword_to_enum(keyw, FALSE);
        } else {
          if (!head) {
            ret = E_RETURN_ERROR;
            goto out;
          }
          (*head)->type_abs = keyword_to_enum(keyw, TRUE);
          (*head)->type = E_TYPE_BASIC;
          (*head)->type_u.type_basic = salloc(struct type_basic);
          (*head)->type_u.type_basic->type_basic = E_TYPE_BASIC_INT;
          (*head)->type_u.type_basic->type_basic_u.type_basic_int =
              salloc(struct type_basic_int);
          (*head)->type_u.type_basic->type_basic_u.type_basic_int->sign = csign;
          csign = E_SIGN_NONE;
          (*head)
              ->type_u.type_basic->type_basic_u.type_basic_int->type_basic_int =
              keyword_to_enum(keyw, FALSE);
          prev = head;
          head = NULL;
        }
      } break;
      case E_KEYWORD_DOUBLE:
      case E_KEYWORD_FLOAT:
      case E_KEYWORD_LDOUBLE: {
        if (!head) {
          ret = E_RETURN_ERROR;
          goto out;
        }
        if (csign != E_SIGN_NONE) {
          ret = E_RETURN_ERROR;
          goto out;
        }
        (*head)->type_abs =
            keyword_to_enum(tokens[*ic].value.keyword.keyword, TRUE);
        (*head)->type = E_TYPE_BASIC;
        (*head)->type_u.type_basic = salloc(struct type_basic);
        (*head)->type_u.type_basic->type_basic = E_TYPE_BASIC_FLOAT;
        (*head)->type_u.type_basic->type_basic_u.type_basic_float =
            salloc(struct type_basic_float);
        (*head)
            ->type_u.type_basic->type_basic_u.type_basic_float
            ->type_basic_float =
            keyword_to_enum(tokens[*ic].value.keyword.keyword, FALSE);
        prev = head;
        head = NULL;
      } break;
      case E_KEYWORD_CONST:
      case E_KEYWORD_VOLATILE: {
        cv = keyword_to_enum(tokens[*ic].value.keyword.keyword, FALSE);
        switch ((*prev)->type_abs) {
        case E_TYPE_ABS_VOID:
        case E_TYPE_ABS_CHAR:
        case E_TYPE_ABS_SHORT:
        case E_TYPE_ABS_INT:
        case E_TYPE_ABS_LONG:
        case E_TYPE_ABS_FLOAT:
        case E_TYPE_ABS_DOUBLE:
        case E_TYPE_ABS_LDOUBLE:
        case E_TYPE_ABS_ENUM:
        case E_TYPE_ABS_STRUCT:
        case E_TYPE_ABS_UNION: {
          if ((*prev)->cv & cv) {
            ret = E_RETURN_ERROR;
            goto out;
          } else {
            (*prev)->cv |= cv;
          }
        } break;
        default: {
          if ((*head)->cv & cv) {
            ret = E_RETURN_ERROR;
            goto out;
          } else {
            (*head)->cv |=
                keyword_to_enum(tokens[*ic].value.keyword.keyword, FALSE);
          }
        } break;
        }
      } break;
      case E_KEYWORD_SIGNED:
      case E_KEYWORD_UNSIGNED: {
        sign = keyword_to_enum(tokens[*ic].value.keyword.keyword, FALSE);
        switch ((*prev)->type_abs) {
        case E_TYPE_ABS_CHAR:
        case E_TYPE_ABS_SHORT:
        case E_TYPE_ABS_INT:
        case E_TYPE_ABS_LONG: {
          if ((*prev)->type_u.type_basic->type_basic_u.type_basic_int->sign !=
              E_SIGN_NONE) {
            ret = E_RETURN_ERROR;
            goto out;
          } else {
            (*prev)->type_u.type_basic->type_basic_u.type_basic_int->sign =
                sign;
          }
        } break;
        default: {
          if (csign != E_SIGN_NONE) {
            ret = E_RETURN_ERROR;
            goto out;
          } else {
            csign = sign;
          }
        } break;
        }
      } break;
      case E_KEYWORD_VOID: {
        if (!head) {
          ret = E_RETURN_ERROR;
          goto out;
        }
        if (csign != E_SIGN_NONE) {
          ret = E_RETURN_ERROR;
          goto out;
        }
        (*head)->type_abs = E_TYPE_ABS_VOID;
        (*head)->type = E_TYPE_VOID;
        (*head)->type_u.type_void = salloc(struct type_void);
        prev = head;
        head = NULL;
      } break;
      case E_KEYWORD_ENUM: {
        if (!head) {
          ret = E_RETURN_ERROR;
          goto out;
        }
        if (csign != E_SIGN_NONE) {
          ret = E_RETURN_ERROR;
          goto out;
        }
        (*head)->type_abs = E_TYPE_ABS_ENUM;
        (*head)->type = E_TYPE_ENUM;
        (*head)->type_u.type_enum = salloc(struct type_enum);
        (*head)->type_u.type_enum->name =
            strdup(tokens[*ic].value.keyword.value.name);
        prev = head;
        head = NULL;
      } break;
      case E_KEYWORD_STRUCT: {
        if (!head) {
          ret = E_RETURN_ERROR;
          goto out;
        }
        if (csign != E_SIGN_NONE) {
          ret = E_RETURN_ERROR;
          goto out;
        }
        (*head)->type_abs = E_TYPE_ABS_STRUCT;
        (*head)->type = E_TYPE_DERIV;
        (*head)->type_u.type_deriv = salloc(struct type_deriv);
        (*head)->type_u.type_deriv->type_deriv = E_TYPE_DERIV_STRUCT;
        (*head)->type_u.type_deriv->type_deriv_u.type_deriv_struct =
            salloc(struct type_deriv_struct);
        (*head)->type_u.type_deriv->type_deriv_u.type_deriv_struct->name =
            strdup(tokens[*ic].value.name);
        prev = head;
        head = NULL;
      } break;
      case E_KEYWORD_UNION: {
        if (!head) {
          ret = E_RETURN_ERROR;
          goto out;
        }
        if (csign != E_SIGN_NONE) {
          ret = E_RETURN_ERROR;
          goto out;
        }
        (*head)->type_abs = E_TYPE_ABS_UNION;
        (*head)->type = E_TYPE_DERIV;
        (*head)->type_u.type_deriv = salloc(struct type_deriv);
        (*head)->type_u.type_deriv->type_deriv = E_TYPE_DERIV_UNION;
        (*head)->type_u.type_deriv->type_deriv_u.type_deriv_union =
            salloc(struct type_deriv_union);
        (*head)->type_u.type_deriv->type_deriv_u.type_deriv_union->name =
            strdup(tokens[*ic].value.name);
        prev = head;
        head = NULL;
      } break;
      }
      ret = parse_next_token(lang, tokens, size, ic, il, ir,
                             (lang == E_LANG_C) ? E_MOVE_LEFT : E_MOVE_RIGHT);
    } break;
    }
  }

out:;
  if (head) {
    ret = E_RETURN_ERROR;
  }
  if (parens != 0) {
    ret = E_RETURN_ERROR;
  }
  if (csign != E_SIGN_NONE) {
    ret = E_RETURN_ERROR;
  }

  return ((ret == E_RETURN_ERROR) ? E_RETURN_ERROR : E_RETURN_TRUE);
}

enum e_return parse_seek_start(enum e_lang lang, const struct token *tokens,
                               size_t size, bool_t declaration, size_t *ic) {
  size_t b;
  size_t e;

  if (size == 0) {
    return E_RETURN_ERROR;
  }

  if (lang == E_LANG_C) {
    if (declaration) {
      while (*ic < size && tokens[*ic].token != E_TOKEN_SEMICOLON &&
             tokens[*ic].token != E_TOKEN_NAME) {
        ++*ic;
      }
      if (*ic < size && tokens[*ic].token == E_TOKEN_NAME) {
        return E_RETURN_TRUE;
      } else {
        return E_RETURN_ERROR;
      }
    } else {
      while (*ic < size && tokens[*ic].token != E_TOKEN_SEMICOLON) {
        if (tokens[*ic].token == E_TOKEN_OPAREN) {
          b = *ic + 1;
        } else if (tokens[*ic].token == E_TOKEN_CPAREN) {
          e = *ic;
          break;
        } else {
          ++*ic;
        }
      }
      if (*ic >= size || tokens[*ic].token == E_TOKEN_SEMICOLON) {
        b = 0;
        e = size;
      }

      for (*ic = b; *ic < e; ++*ic) {
        if (tokens[*ic].token == E_TOKEN_ARRAY) {
          break;
        }
      }
      if (*ic >= e) {
        *ic = e - 1;
      }

      if (!(*ic >= b && *ic < e)) {
        return E_RETURN_ERROR;
      } else {
        return E_RETURN_TRUE;
      }
    }
  } else if (lang == E_LANG_ENG) {
    if (tokens[*ic].token == E_TOKEN_NAME || !declaration) {
      return E_RETURN_TRUE;
    } else {
      return E_RETURN_ERROR;
    }
  } else {
    return E_RETURN_ERROR;
  }
}

enum e_return parse_next_token(enum e_lang lang, const struct token *tokens,
                               size_t size, size_t *ic, size_t *il, size_t *ir,
                               enum e_move move) {
  bool_t cmr;
  bool_t cml;

  (void)lang;

  cmr = (tokens[*ir].token != E_TOKEN_SEMICOLON) && ((*ir + 1) < size) ? TRUE
                                                                       : FALSE;
  cml = *il != 0 ? TRUE : FALSE;

  switch (move) {
  case E_MOVE_RIGHT: {
    if (cmr) {
      *ic = ++*ir;
    } else if (cml) {
      *ic = --*il;
    } else {
      return E_RETURN_FALSE;
    }
  } break;
  case E_MOVE_LEFT: {
    if (cml) {
      *ic = --*il;
    } else if (cmr) {
      *ic = ++*ir;
    } else {
      return E_RETURN_FALSE;
    }
  } break;
  }

  return E_RETURN_TRUE;
}

enum e_return parse_next_fpar(enum e_lang lang, const struct token *tokens,
                              size_t size, size_t *ic, size_t *il, size_t *ir,
                              const struct token **ptokens, size_t *psize) {
  long parens;

  (void)lang;

  switch (tokens[*ic].token) {
  case E_TOKEN_OPAREN:
  case E_TOKEN_COMMA: {
    if (parse_next_token(lang, tokens, size, ic, il, ir, E_MOVE_RIGHT) ==
        E_RETURN_FALSE) {
      return E_RETURN_ERROR;
    }
    if (tokens[*ic].token == E_TOKEN_CPAREN) {
      return E_RETURN_FALSE;
    }
    *ptokens = &tokens[*ic];
    *psize = 0;
    parens = 0;
    for (;;) {
      if (parens == 0 && (tokens[*ic].token == E_TOKEN_COMMA ||
                          tokens[*ic].token == E_TOKEN_CPAREN)) {
        break;
      }
      if (tokens[*ic].token == E_TOKEN_OPAREN) {
        ++parens;
      } else if (tokens[*ic].token == E_TOKEN_CPAREN) {
        --parens;
      }
      if (parens < 0) {
        return E_RETURN_ERROR;
      }
      if (parse_next_token(lang, tokens, size, ic, il, ir, E_MOVE_RIGHT) !=
          E_RETURN_TRUE) {
        return E_RETURN_ERROR;
      }
      ++*psize;
    }

    if (*psize > 0) {
      return E_RETURN_TRUE;
    } else {
      return E_RETURN_ERROR;
    }
  } break;
  case E_TOKEN_CPAREN: {
    return E_RETURN_FALSE;
  } break;
  default: {
    return E_RETURN_ERROR;
  } break;
  }
}

void serialize(enum e_lang lang, const struct declaration *decl) {
  char str[MAX_LINE];

  serialize_decl(lang, decl, str);

  if (lang == E_LANG_ENG) {
    printf("%s\n", str);
  } else if (lang == E_LANG_C) {
    printf("%s;\n", str);
  }
}

void serialize_decl(enum e_lang lang, const struct declaration *decl,
                    char *str) {
  switch (lang) {
  case E_LANG_ENG: {
    sprintf(str, "%s: ", decl->name);
    serialize_type(lang, decl->type, str);
  } break;
  case E_LANG_C: {
    strcpy(str, decl->name);
    serialize_type(lang, decl->type, str);
  } break;
  }
}

void serialize_type(enum e_lang lang, const struct type *type, char *str) {
  char temp[MAX_LINE];
  char ptemp[MAX_LINE];
  size_t i;

  switch (type->type) {
  case E_TYPE_VOID: {
    if (lang == E_LANG_ENG) {
      sprintf(temp, "%s %s%s", str, cv_to_str(type->cv, 1),
              type_to_str(type->type_abs));
    } else if (lang == E_LANG_C) {
      sprintf(temp, "%s%s %s", cv_to_str(type->cv, 1),
              type_to_str(type->type_abs), str);
    }
    strcpy(str, temp);
  } break;
  case E_TYPE_BASIC: {
    if (lang == E_LANG_ENG) {
      sprintf(temp, "%s%s", str, cv_to_str(type->cv, -1));
      strcpy(str, temp);
    }
    switch (type->type_u.type_basic->type_basic) {
    case E_TYPE_BASIC_INT: {
      if (lang == E_LANG_C) {
        sprintf(temp, "%s %s", type_to_str(type->type_abs), str);
        strcpy(str, temp);
      }
      switch (type->type_u.type_basic->type_basic_u.type_basic_int->sign) {
      case E_SIGN_NONE: {
      } break;
      case E_SIGN_SIGNED: {
        if (lang == E_LANG_ENG) {
          sprintf(temp, "%s signed", str);
        } else if (lang == E_LANG_C) {
          sprintf(temp, "signed %s", str);
        }
        strcpy(str, temp);
      } break;
      case E_SIGN_UNSIGNED: {
        if (lang == E_LANG_ENG) {
          sprintf(temp, "%s unsigned", str);
        } else if (lang == E_LANG_C) {
          sprintf(temp, "unsigned %s", str);
        }
        strcpy(str, temp);
      } break;
      }
      if (lang == E_LANG_ENG) {
        sprintf(temp, "%s %s", str, type_to_str(type->type_abs));
        strcpy(str, temp);
      }
    } break;
    case E_TYPE_BASIC_FLOAT: {
      if (lang == E_LANG_ENG) {
        sprintf(temp, "%s %s", str, type_to_str(type->type_abs));
      } else if (lang == E_LANG_C) {
        sprintf(temp, "%s %s", type_to_str(type->type_abs), str);
      }
      strcpy(str, temp);
    } break;
    }
    if (lang == E_LANG_C) {
      sprintf(temp, "%s%s", cv_to_str(type->cv, 1), str);
      strcpy(str, temp);
    }
  } break;
  case E_TYPE_ENUM: {
    if (lang == E_LANG_ENG) {
      sprintf(temp, "%s enum %s", str, type->type_u.type_enum->name);
    } else if (lang == E_LANG_C) {
      sprintf(temp, "enum %s %s", type->type_u.type_enum->name, str);
    }
    strcpy(str, temp);

  } break;
  case E_TYPE_DERIV: {
    switch (type->type_u.type_deriv->type_deriv) {
    case E_TYPE_DERIV_ARRAY: {

      if (lang == E_LANG_ENG) {
        if (type->type_u.type_deriv->type_deriv_u.type_deriv_array->size != 0) {
          sprintf(temp, "%s array[%lu] of", str,
                  type->type_u.type_deriv->type_deriv_u.type_deriv_array->size);
        } else {
          sprintf(temp, "%s array[] of", str);
        }
      } else if (lang == E_LANG_C) {
        if (type->type_u.type_deriv->type_deriv_u.type_deriv_array->size != 0) {
          sprintf(temp, "%s[%lu]", str,
                  type->type_u.type_deriv->type_deriv_u.type_deriv_array->size);
        } else {
          sprintf(temp, "%s[]", str);
        }
      }
      strcpy(str, temp);
      serialize_type(
          lang, type->type_u.type_deriv->type_deriv_u.type_deriv_array->type,
          str);
    } break;
    case E_TYPE_DERIV_STRUCT: {
      if (lang == E_LANG_ENG) {
        sprintf(temp, "%s struct %s", str,
                type->type_u.type_deriv->type_deriv_u.type_deriv_struct->name);
      } else if (lang == E_LANG_C) {
        sprintf(temp, "enum %s %s",
                type->type_u.type_deriv->type_deriv_u.type_deriv_struct->name,
                str);
      }
      strcpy(str, temp);
    } break;
    case E_TYPE_DERIV_UNION: {
      if (lang == E_LANG_ENG) {
        sprintf(temp, "%s union %s", str,
                type->type_u.type_deriv->type_deriv_u.type_deriv_union->name);
      } else if (lang == E_LANG_C) {
        sprintf(temp, "enum %s %s",
                type->type_u.type_deriv->type_deriv_u.type_deriv_union->name,
                str);
      }
      strcpy(str, temp);
    } break;
    case E_TYPE_DERIV_FUNC: {
      if (lang == E_LANG_ENG) {
        sprintf(temp, "%s function", str);
      } else if (lang == E_LANG_C) {
        sprintf(temp, "%s(", str);
      }
      strcpy(str, temp);
      if (type->type_u.type_deriv->type_deriv_u.type_deriv_func
              ->type_params_len != 0) {
        if (lang == E_LANG_ENG) {
          sprintf(temp, "%s (", str);
          strcpy(str, temp);
        }
        for (i = 0; i < type->type_u.type_deriv->type_deriv_u.type_deriv_func
                            ->type_params_len;
             ++i) {
          ptemp[0] = '\0';
          serialize_type(lang,
                         type->type_u.type_deriv->type_deriv_u.type_deriv_func
                             ->type_params[i],
                         ptemp);
          sprintf(temp, "%s%s%s", str, (i != 0 ? ", " : ""), ptemp);
          strcpy(str, temp);
        }
        if (lang == E_LANG_ENG) {
          sprintf(temp, "%s)", str);
          strcpy(str, temp);
        }
      }
      if (lang == E_LANG_ENG) {
        sprintf(temp, "%s returning", str);
      } else if (lang == E_LANG_C) {
        sprintf(temp, "%s)", str);
      }
      strcpy(str, temp);
      serialize_type(
          lang, type->type_u.type_deriv->type_deriv_u.type_deriv_func->type_ret,
          str);

    } break;
    case E_TYPE_DERIV_PTR: {
      if (lang == E_LANG_ENG) {
        sprintf(temp, "%s %spointer to", str, cv_to_str(type->cv, 1));
      } else if (lang == E_LANG_C) {
        switch (type->type_u.type_deriv->type_deriv_u.type_deriv_ptr->type
                    ->type_abs) {
        case E_TYPE_ABS_ARRAY:
        case E_TYPE_ABS_FUNC: {
          sprintf(temp, "(*%s%s)", cv_to_str(type->cv, 1), str);
        } break;
        default: {
          sprintf(temp, "*%s%s", cv_to_str(type->cv, 1), str);
        } break;
        }
      }
      strcpy(str, temp);
      serialize_type(lang,
                     type->type_u.type_deriv->type_deriv_u.type_deriv_ptr->type,
                     str);
    } break;
    }
  } break;
  }
}

const char *cv_to_str(enum e_cv cv, int space) {
  static char out[17];
  /* static char out[(strlen(" const volatile ")+1)]; */

  out[0] = '\0';

  if (cv != E_CV_NONE && space <= 0) {
    strcat(out, " ");
  }

  if (cv != E_CV_NONE) {
    if (cv & E_CV_CONST && cv & E_CV_VOLATILE) {
      strcat(out, "const volatile");
    } else if (cv & E_CV_CONST) {
      strcat(out, "const");
    } else if (cv & E_CV_VOLATILE) {
      strcat(out, "volatile");
    }
  }

  if (cv != E_CV_NONE && space >= 0) {
    strcat(out, " ");
  }

  return out;
}

int str_to_keyword(const char *str) {
  if (strcmp(str, "char") == 0) {
    return E_KEYWORD_CHAR;
  } else if (strcmp(str, "const") == 0) {
    return E_KEYWORD_CONST;
  } else if (strcmp(str, "double") == 0) {
    return E_KEYWORD_DOUBLE;
  } else if (strcmp(str, "enum") == 0) {
    return E_KEYWORD_ENUM;
  } else if (strcmp(str, "float") == 0) {
    return E_KEYWORD_FLOAT;
  } else if (strcmp(str, "int") == 0) {
    return E_KEYWORD_INT;
  } else if (strcmp(str, "long") == 0) {
    return E_KEYWORD_LONG;
  } else if (strcmp(str, "short") == 0) {
    return E_KEYWORD_SHORT;
  } else if (strcmp(str, "signed") == 0) {
    return E_KEYWORD_SIGNED;
  } else if (strcmp(str, "struct") == 0) {
    return E_KEYWORD_STRUCT;
  } else if (strcmp(str, "union") == 0) {
    return E_KEYWORD_UNION;
  } else if (strcmp(str, "unsigned") == 0) {
    return E_KEYWORD_UNSIGNED;
  } else if (strcmp(str, "void") == 0) {
    return E_KEYWORD_VOID;
  } else if (strcmp(str, "volatile") == 0) {
    return E_KEYWORD_VOLATILE;
  } else {
    return -1;
  }
}

int keyword_to_enum(enum e_keyword keyword, bool_t abs) {
  if (abs) {
    switch (keyword) {
    case E_KEYWORD_CHAR: {
      return E_TYPE_ABS_CHAR;
    } break;
    case E_KEYWORD_DOUBLE: {
      return E_TYPE_ABS_DOUBLE;
    } break;
    case E_KEYWORD_ENUM: {
      return E_TYPE_ABS_ENUM;
    } break;
    case E_KEYWORD_FLOAT: {
      return E_TYPE_ABS_FLOAT;
    } break;
    case E_KEYWORD_INT: {
      return E_TYPE_ABS_INT;
    } break;
    case E_KEYWORD_LDOUBLE: {
      return E_TYPE_ABS_LDOUBLE;
    } break;
    case E_KEYWORD_LONG: {
      return E_TYPE_ABS_LONG;
    } break;
    case E_KEYWORD_SHORT: {
      return E_TYPE_ABS_SHORT;
    } break;
    case E_KEYWORD_STRUCT: {
      return E_TYPE_ABS_STRUCT;
    } break;
    case E_KEYWORD_UNION: {
      return E_TYPE_ABS_UNION;
    } break;
    case E_KEYWORD_VOID: {
      return E_TYPE_ABS_VOID;
    } break;
    default: {
      return -1;
    } break;
    }
  } else {
    switch (keyword) {
    case E_KEYWORD_CHAR: {
      return E_TYPE_BASIC_INT_CHAR;
    } break;
    case E_KEYWORD_CONST: {
      return E_CV_CONST;
    } break;
    case E_KEYWORD_DOUBLE: {
      return E_TYPE_BASIC_FLOAT_DOUBLE;
    } break;
    case E_KEYWORD_ENUM: {
      return E_TYPE_ENUM;
    } break;
    case E_KEYWORD_FLOAT: {
      return E_TYPE_BASIC_FLOAT_FLOAT;
    } break;
    case E_KEYWORD_INT: {
      return E_TYPE_BASIC_INT_INT;
    } break;
    case E_KEYWORD_LDOUBLE: {
      return E_TYPE_BASIC_FLOAT_LDOUBLE;
    } break;
    case E_KEYWORD_LONG: {
      return E_TYPE_BASIC_INT_LONG;
    } break;
    case E_KEYWORD_SHORT: {
      return E_TYPE_BASIC_INT_SHORT;
    } break;
    case E_KEYWORD_SIGNED: {
      return E_SIGN_SIGNED;
    } break;
    case E_KEYWORD_STRUCT: {
      return E_TYPE_DERIV_STRUCT;
    } break;
    case E_KEYWORD_UNION: {
      return E_TYPE_DERIV_UNION;
    } break;
    case E_KEYWORD_UNSIGNED: {
      return E_SIGN_UNSIGNED;
    } break;
    case E_KEYWORD_VOID: {
      return E_TYPE_VOID;
    } break;
    case E_KEYWORD_VOLATILE: {
      return E_CV_VOLATILE;
    } break;
    default: {
      return -1;
    } break;
    }
  }
}

const char *type_to_str(enum e_type_abs type) {
  switch (type) {
  case E_TYPE_ABS_VOID: {
    return "void";
  } break;
  case E_TYPE_ABS_CHAR: {
    return "char";
  } break;
  case E_TYPE_ABS_SHORT: {
    return "short";
  } break;
  case E_TYPE_ABS_INT: {
    return "int";
  } break;
  case E_TYPE_ABS_LONG: {
    return "long";
  } break;
  case E_TYPE_ABS_FLOAT: {
    return "float";
  } break;
  case E_TYPE_ABS_DOUBLE: {
    return "double";
  } break;
  case E_TYPE_ABS_LDOUBLE: {
    return "long double";
  } break;
  default: {
    return "";
  } break;
  }
}

int main(int argc, char *argv[]) {
  enum e_prog prog;
  enum e_lang plang;
  enum e_lang slang;
  char line[MAX_LINE];
  struct token tokens[MAX_LINE];
  size_t tokens_size;
  struct declaration decl;
  size_t i;

  if (argc != 2) {
    return EXIT_FAILURE;
  } else if (strcmp(argv[1], "dcl") == 0) {
    prog = E_PROG_DCL;
  } else if (strcmp(argv[1], "undcl") == 0) {
    prog = E_PROG_UNDCL;
  } else {
    return EXIT_FAILURE;
  }

  switch (prog) {
  case E_PROG_DCL: {
    plang = E_LANG_C;
    slang = E_LANG_ENG;
  } break;
  case E_PROG_UNDCL: {
    plang = E_LANG_ENG;
    slang = E_LANG_C;
  } break;
  }

  while (!feof(stdin) && fgets(line, MAX_LINE, stdin)) {
    tokens_size = MAX_LINE;
    if (lex(plang, line, tokens, &tokens_size) == E_RETURN_ERROR) {
      fprintf(stderr, "lex error\n");
      return EXIT_FAILURE;
    }
    if (parse(plang, tokens, tokens_size, &decl) == E_RETURN_ERROR) {
      fprintf(stderr, "parse error\n");
      return EXIT_FAILURE;
    }
    serialize(slang, &decl);
    for (i = 0; i < tokens_size; ++i) {
      dtor_token(&tokens[i]);
    }
    dtor_declaration(&decl);
  }

  return EXIT_SUCCESS;
}

/* usage example
 * echo "char (*(*x())[])();" | ./a.out dcl
 * echo "x () * [] * () char;" | ./a.out undcl
 */
