int strend(const char *s, const char *t) {
  const char *u;

  for (; *s != '\0'; ++s) {
    for (u = s; (*u == *t) && *u != '\0' && *t != '\0'; ++u, ++t)
      ;
    if (*u == '\0' && *t == '\0') {
      return 1;
    }
  }
  return 0;
}
