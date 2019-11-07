#include <stdio.h>

#define NUM_CHARS 20

int main()
{
  FILE* random_file = fopen("/dev/random", "r");

  for (size_t i = 0; i < NUM_CHARS; ++i)
  {
    putchar(fgetc(random_file));
  }
  putchar('\n');

  fclose(random_file);
  return 0;
}
