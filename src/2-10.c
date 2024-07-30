char lower(char c) {
  return ((c >= 'A' && c <= 'Z') ? (c + ('a' - 'A')) : (c));
}
