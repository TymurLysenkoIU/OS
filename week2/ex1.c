#include <limits.h>
#include <float.h>
#include <stdio.h>

void main() {
  int i = INT_MAX;
  float f = FLT_MAX;
  double d = DBL_MAX;

  printf("sizeof(int) = %d; INT_MAX = %d\n", sizeof(int), i);
  printf("sizeof(float) = %d; FLT_MAX = %e\n", sizeof(float), f);
  printf("sizeof(double) = %d; DBL_MAX = %e\n", sizeof(double), d);
}
