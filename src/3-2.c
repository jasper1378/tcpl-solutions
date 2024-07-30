int escape(char *s, const char *t) {
  for (; *t != '\0'; ++s, ++t) {
    switch (*t) {
    case '\\': {
      *s++ = '\\';
      *s = '\\';
    } break;
    case '\n': {
      *s++ = '\\';
      *s = 'n';
    } break;
    case '\t': {
      *s++ = '\\';
      *s = 't';
    } break;
    default: {
      *s = *t;
    };
    }
  }
  *s = '\0';
  return 0;
}

int unescape(char *s, const char *t) {
  for (; *t != '\0'; ++s, ++t) {
    switch (*t) {
    case '\\': {
      switch (*++t) {
      case '\\': {
        *s = '\\';
      } break;
      case 'n': {
        *s = '\n';
      } break;
      case 't': {
        *s = '\t';
      } break;
      default: {
        return -1;
      };
      }
    } break;
    default: {
      *s = *t;
    } break;
    }
  }
  *s = '\0';
  return 0;
}
