#include <assert.h>
#include <errno.h>

int hex_digit_to_dec(char d) {
  if (d >= '0' && d <= '9') {
    return d - '0';
  } else if (d >= 'a' && d <= 'f') {
    return d - 'a' + 10;
  } else if (d >= 'A' && d <= 'F') {
    return d - 'A' + 10;
  } else {
    return -1;
  }
}

int htoi(const char *str, int *err) {
  const char *p;
  int s;
  int r;
  int d;

  *err = 0;
  p = str;
  s = 1;
  r = 0;

  if (*p == '-') {
    s = -1;
    ++p;
  } else if (*p == '+') {
    s = 1;
    ++p;
  }

  if (*p == '0' && (p[1] == 'x' || p[1] == 'X')) {
    p += 2;
  }

  for (; *p != '\0'; ++p) {
    d = hex_digit_to_dec(*p);
    if (d == -1) {
      *err = -1;
    }
    r = r * 16 + d;
  }

  return s * r;
}

int main() {
  int err;
  assert(htoi("123abc", &err) == 0x123abc);
  assert(htoi("0x123abc", &err) == 0x123abc);
  assert(htoi("0X123abc", &err) == 0x123abc);
  assert(htoi("-123abc", &err) == -0x123abc);
  assert(htoi("-0x123abc", &err) == -0x123abc);
  assert(htoi("-0X123abc", &err) == -0x123abc);
  assert(htoi("+123abc", &err) == +0x123abc);
  assert(htoi("+0x123abc", &err) == +0x123abc);
  assert(htoi("+0X123abc", &err) == +0x123abc);
}
