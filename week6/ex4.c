#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void kill_handler(int sig_num)
{
  printf("Received signal %d. Stopping the process.\n", sig_num);
  exit(0);
}

void usr1_handler(int sig_num)
{
  printf("Handling user signal: SIGUSR1 %d\n", sig_num);
}

void stop_handler(int sig_num)
{
  printf("Handling stop signal (no): SIGSTOP %d\n", sig_num);
}

int main()
{
  signal(SIGUSR1, usr1_handler); // The handler will be executed upon receiving the signal
  signal(SIGKILL, kill_handler); // Cannot be caught or ignored, so the handler won't execute
  signal(SIGSTOP, stop_handler); // Cannot be caught or ignored, so the handler won't execute

  while (1);

  return 0;
}
