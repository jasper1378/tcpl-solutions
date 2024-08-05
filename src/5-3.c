void strcat(char *s, const char *t) {
  while (*s != '\0')
    ++s;
  while ((*s++ = *t++) != '\0')
    ;
}
