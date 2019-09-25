#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void int_handler(int sig_num)
{
  printf("Received signal %d. Stopping the process.\n", sig_num);
  exit(0);
}

int main()
{
  signal(SIGINT, int_handler);

  while (1);

  return 0;
}
