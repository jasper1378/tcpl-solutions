#include <stdio.h>

float celsius(float fahr) { return (5.0 / 9.0) * (fahr - 32.0); }

int main() {
  float fahr;
  float lower;
  float upper;
  float step;

  lower = 0;
  upper = 300;
  step = 20;

  fahr = lower;
  while (fahr <= upper) {
    printf("%3.0f %6.1f\n", fahr, celsius(fahr));
    fahr = fahr + step;
  }
}
