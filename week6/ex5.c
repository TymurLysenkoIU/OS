#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

void term_handler(int sig_num)
{
  printf("Child received SIGTERM, stopping the child.\n");
  exit(0);
}

int main()
{
  pid_t pid = fork();

  if (pid == -1)
  { // error forking a process
    printf("Could not fork a process, try to rerun the program.\n");
  }
  else if (pid == 0)
  { // child code
    signal(SIGTERM, term_handler); // The handler will be executed upon receiving the signal

    while (1)
    {
      printf("I'm  alive\n");
      sleep(1);
    }
  }
  else
  { // parent code
    sleep(10);
    kill(pid, SIGTERM);
    printf("Sent SIGTERM to the child, finishing the parent.\n");
  }

  return 0;
}
