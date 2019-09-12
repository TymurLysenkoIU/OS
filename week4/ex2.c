#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  for (unsigned int i = 0; i < 5; ++i)
  {
    fork();
  }
  printf("Finished forking\n");
  sleep(5);

  return 0;
}
