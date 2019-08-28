#include <stdio.h>
#include <stdlib.h>

void swap(int* x, int* y) {
  int x_temp = *x;
  *x = *y;
  *y = x_temp;
}

void main(int argc, char* argv[]) {
  int x, y;
  sscanf(argv[1], "%d", &x);
  sscanf(argv[2], "%d", &y);

  swap(&x, &y);

  printf("x = %d\ny = %d\n", x, y);
}
