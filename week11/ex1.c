#include <sys/mman.h>
#include <sys/io.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
  char* str_to_write = "This is a nice day";
  size_t str_size = strlen(str_to_write) + 1;

  FILE* file_ptr = NULL;
  if (file_ptr = fopen("ex1.txt", "r+"))
  {
    int fd = fileno(file_ptr);

    void* mapped_file = NULL;
    if ((mapped_file = mmap(
      NULL,
      str_size,
      PROT_READ | PROT_WRITE,
      MAP_SHARED,
      fd,
      0
    )) != MAP_FAILED)
    {
      ftruncate(fd, str_size - 1);
      memcpy(mapped_file, str_to_write, str_size);
    }
    else
    {
      printf("Could not map the file!\n");
      printf("%s\n", strerror(errno));
    }

    fclose(file_ptr);
  }
  else
  {
    printf("Could not open the file!\n");
  }

  return 0;
}
