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
      low = mid;
    }
  }
  if (n == v[low]) {
    return low;
  }
  return -1;
}
