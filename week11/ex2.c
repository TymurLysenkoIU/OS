#include <stdio.h>
#include <unistd.h>

#define BUFF_SIZE 6

int main()
{
  char buff[BUFF_SIZE];
  setvbuf(stdout, buff, _IOLBF, BUFF_SIZE);

  printf("H");
  sleep(1);
  printf("e");
  sleep(1);
  printf("l");
  sleep(1);
  printf("l");
  sleep(1);
  printf("o");
  sleep(1);
  printf("\n");

  return 0;
}
