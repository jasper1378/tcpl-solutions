#include <stdio.h>
#include <string.h>

int isupper_1(int c);
int isupper_2(int c);
int isupper_3(int c);

int isupper_1(int c) { return (('A' <= c) && (c <= 'Z')); }

int isupper_2(int c) {
  switch (c) {
  case 'A': {
    return 1;
  } break;
  case 'B': {
    return 1;
  } break;
  case 'C': {
    return 1;
  } break;
  case 'D': {
    return 1;
  } break;
  case 'E': {
    return 1;
  } break;
  case 'F': {
    return 1;
  } break;
  case 'G': {
    return 1;
  } break;
  case 'H': {
    return 1;
  } break;
  case 'I': {
    return 1;
  } break;
  case 'J': {
    return 1;
  } break;
  case 'K': {
    return 1;
  } break;
  case 'L': {
    return 1;
  } break;
  case 'M': {
    return 1;
  } break;
  case 'N': {
    return 1;
  } break;
  case 'O': {
    return 1;
  } break;
  case 'P': {
    return 1;
  } break;
  case 'Q': {
    return 1;
  } break;
  case 'R': {
    return 1;
  } break;
  case 'S': {
    return 1;
  } break;
  case 'T': {
    return 1;
  } break;
  case 'U': {
    return 1;
  } break;
  case 'V': {
    return 1;
  } break;
  case 'W': {
    return 1;
  } break;
  case 'X': {
    return 1;
  } break;
  case 'Y': {
    return 1;
  } break;
  case 'Z': {
    return 1;
  } break;
  default: {
    return 0;
  } break;
  }
}

int isupper_3(int c) {
  return ((strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ", c)) != NULL);
}

int main() {
  char c;
  while (scanf(" %c", &c) == 1) {
    printf("isupper_1('%c'): %d\n", c, isupper_1(c));
    printf("isupper_2('%c'): %d\n", c, isupper_2(c));
    printf("isupper_3('%c'): %d\n", c, isupper_3(c));
    putchar('\n');
  }
  return 0;
}
