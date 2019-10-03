#include <stdlib.h>
#include <stdio.h>

int main()
{
  printf("Enter a natural number excluding 0:\n");

  unsigned int N = 1;
  scanf("%u", &N);

  size_t* arr = malloc(N * sizeof(size_t));

  for (size_t i = 0; i < N; ++i)
  {
    arr[i] = i;
    printf("%u\n", arr[i]);
  }

  free(arr);
  return 0;
}
