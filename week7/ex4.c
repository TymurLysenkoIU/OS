#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5
#define NEW_SIZE 10

void* myrealloc(void* ptr, size_t new_size, size_t old_size)
{
  if (new_size)
  {
    if (ptr)
    {
      void* new_mem = malloc(new_size);

      memcpy(new_mem, ptr, new_size > old_size ? old_size : new_size);
      free(ptr);

      return new_mem;
    }
    else
    {
      return malloc(new_size);
    }
  }
  else
  {
    free(ptr);
    return NULL;
  }
}

int main()
{
  size_t old_size = SIZE * sizeof(int);
  int* arr = malloc(old_size);

  arr = myrealloc(arr, NEW_SIZE * sizeof(int), old_size);

  free(arr);
  return 0;
}
