#include <stdio.h>

int main() {
  float fahr;
  float celsius;
  float lower;
  float upper;
  float step;

  lower = 0;
  upper = 300;
  step = 20;

  celsius = lower;
  while (celsius <= upper) {
    fahr = celsius / (5.0 / 9.0) + 32.0;
    printf("%3.0f %6.1f\n", celsius, fahr);
    celsius = celsius + step;
  }
}
