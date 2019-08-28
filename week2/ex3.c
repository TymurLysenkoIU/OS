#include <stdio.h>

void main(int argc, char* argv[]) {
  int n;
  sscanf(argv[1], "%d", &n);

  for (int i = n - 1; i >= 0; --i) {
    // spaces
    for (int j = 0; j < i; ++j) {
      putchar(' ');
    }

    // stars
    for (int j = 0; j < ((n - i) * 2) - 1; ++j) {
      printf("*");
    }
    printf("\n");
  }
}
