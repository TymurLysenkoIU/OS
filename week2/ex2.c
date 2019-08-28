#include <stdio.h>
#include <stdlib.h>

void main() {
  size_t buffer_size = 0;
  char* read_string = NULL;

  printf("Enter a string:\n");
  int str_len = getline(&read_string, &buffer_size, stdin);

  for (int i = str_len - 2; i >= 0; --i) {
    printf("%c", read_string[i]);
  }
  printf("\n");

  free(read_string);
}
