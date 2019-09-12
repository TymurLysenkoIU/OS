#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  pid_t n;
  n = fork();

  if (n < 0)
  {
    printf("Could not create a child process\n");
  }
  else if (n > 0)
  {
    printf("Hello from parent [PID - %d]\n", n);
  }
  else
  {
    printf("Hello from child [PID - %d]\n", n);
  }

  return 0;
}
