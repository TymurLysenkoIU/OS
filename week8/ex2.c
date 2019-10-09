#include <stdlib.h>
#include <unistd.h>

int main()
{
  for (int i = 0; i < 10; ++i)
  {
    calloc(sizeof(char), 1024 * 1024 * 10);
    sleep(1);
  }

  return 0;
}
