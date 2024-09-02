#include <stdio.h>

#define swap(t_, x_, y_)                                                       \
  {                                                                            \
    t_ z_;                                                                     \
    z_ = x_;                                                                   \
    x_ = y_;                                                                   \
    y_ = z_;                                                                   \
  }

int main() {
  int x;
  int y;

  scanf("%d", &x);
  scanf("%d", &y);
  printf("x: %d, y: %d\n", x, y);
  swap(int, x, y);
  printf("x: %d, y: %d\n", x, y);

  return 0;
}
