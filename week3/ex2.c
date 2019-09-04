#include <stdio.h>

#define ARRAY_SIZE 10

void swap(int* x, int* y)
{
  int x_temp = *x;
  *x = *y;
  *y = x_temp;
}

void bubble_sort(int arr[], unsigned int size)
{
  for (int i = 0; i < size; ++i)
  {
    for (int j = i + 1; j < size; ++j)
    {
      if (arr[i] > arr[j])
      {
        swap(&arr[i], &arr[j]);
      }
    }
  }
}

void print_array(int arr[], unsigned int size)
{
  for (int i = 0; i < size; ++i)
  {
    printf("arr[%d] = %d\n", i, arr[i]);
  }

  printf("\n");
}

int main()
{
  int arr[ARRAY_SIZE] = {8, 9, 7, 1, 2, 6, 8, 10, 12, 59};

  print_array(arr, ARRAY_SIZE);
  bubble_sort(arr, ARRAY_SIZE);
  print_array(arr, ARRAY_SIZE);

  return 0;
}
