void squeeze(char *s1, const char *s2) {
  const char *r;
  char *w;
  const char *s;

  for (r = s1, w = s1; *r != '\0'; ++r) {
    for (s = s2; *s != '\0'; ++s) {
      if (*s == *r) {
        break;
      }
    }
    if (*s == '\0') {
      *w++ = *r;
    }
  }
  *w = '\0';
}
