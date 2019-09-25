#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

#define STR_SIZE 14

int main()
{
  char s1[STR_SIZE] = "Hello, world!",
       s2[STR_SIZE] = "";
  int pipedes[2];

  if (pipe(pipedes))
  {
    printf("Failed to create a pipe, try to rerun the program.\n");
  }
  else
  {
    int read_end = pipedes[0],
        write_end = pipedes[1];
    int pid = fork();
    pid_t parent_pid = getppid(),
          current_pid = getpid();



    if (pid == -1)
    { // error forking a process
      printf("Could not fork a process, try to rerun the program.\n");
    }
    else if (pid == 0)
    { // child code
      read(read_end, s2, STR_SIZE);
      printf(
        "Process %d, child of %d read \"%s\" from the pipe.\n",
        current_pid,
        parent_pid,
        s1
      );
    }
    else
    { // parent code
      printf(
        "Process %d, child of %d writes \"%s\" into the pipe.\n",
        current_pid,
        parent_pid,
        s1
      );
      write(write_end, s1, STR_SIZE);
    }
  }

  return 0;
}
