#include <stdio.h>

int binsearch(int x, int *v, int n) {
  int low;
  int high;
  int mid;

  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if (x < v[mid]) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  if (x == v[low - 1]) {
    return low - 1;
  }
  return -1;
}

int main() {
  int v[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int x;

  scanf("%d", &x);
  printf("%d\n", binsearch(x, v, 10));

  return 0;
}
