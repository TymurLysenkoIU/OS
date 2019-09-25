#include <unistd.h>
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

    write(write_end, s1, STR_SIZE);
    read(read_end, s2, STR_SIZE);

    printf("%s\n", s2);
  }

  return 0;
}
