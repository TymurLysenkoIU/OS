#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
  int pipedes[2];

  if (pipe(pipedes))
  {
    printf("Failed to create a pipe, try to rerun the program.\n");
  }
  else
  {
    int read_end = pipedes[0],
        write_end = pipedes[1];

    printf("Forking the 1-st child...\n");
    pid_t f_pid = fork();

    if (f_pid == -1)
    { // error forking a process
      printf("Could not fork a process, try to rerun the program.\n");
    }
    else if (f_pid == 0)
    { // 1-st child code
      printf("1-st child process created.\n");

      pid_t s_pid;
      read(read_end, &s_pid, sizeof(pid_t));
      printf("1-st child process read 2-nd child PID (%d) from a pipe. Now sleep 3 seconds...\n", s_pid);
      sleep(3);
      printf("1-st child process is awaken, sending SIGSTOP to 2-nd child process...\n");
      kill(s_pid, SIGSTOP);
      printf("1-st child process sends SIGKILL to 2-nd child process...\n");
      kill(s_pid, SIGKILL);
    }
    else
    { // parent code
      printf("Forking the 2-nd child...\n");
      pid_t s_pid = fork();

      if (s_pid == -1)
      { // error forking a process
        printf("Could not fork a process, try to rerun the program.\n");
      }
      else if (s_pid == 0)
      { // 2-nd child code
        printf("2-nd child process created.\n");

        while (1);
      }
      else
      { // parent code
        printf("Parent writes 2-nd child PID (%d) to the pipe.\n", s_pid);
        write(write_end, &s_pid, sizeof(f_pid));
        int status;

        do
        {
          waitpid(s_pid, &status, 0);

          if (WIFSTOPPED(status))
          {
            printf("2-nd child received SIGSTOP.\n");
          }
        }
        while (!WIFEXITED(status) && !WIFSIGNALED(status));

        printf("2-nd child is finished.\n");
      }
    }
  } 

  return 0;
}
