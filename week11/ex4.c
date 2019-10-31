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
  FILE* i_file_ptr = NULL;
  if (i_file_ptr = fopen("ex1.txt", "r"))
  {
    int i_fd = fileno(i_file_ptr);

    struct stat i_stat;
    
    if (fstat(i_fd, &i_stat))
    {
      printf("Could not retreive stats of the input file");
    }
    else
    {
      FILE* o_file_ptr = NULL;
      if (o_file_ptr = fopen("ex1.memcpy.txt", "w+"))
      {
        int o_fd = fileno(o_file_ptr);

        void* i_mapped = NULL;
        if ((i_mapped = mmap(NULL, i_stat.st_size, PROT_READ, MAP_PRIVATE, i_fd, 0)) != MAP_FAILED)
        {
          void* o_mapped = NULL;
          if ((o_mapped = mmap(NULL, i_stat.st_size, PROT_WRITE, MAP_SHARED, o_fd, 0)) != MAP_FAILED)
          {
            ftruncate(o_fd, i_stat.st_size);
            memcpy(o_mapped, i_mapped, i_stat.st_size);
          }
          else
          {
            printf("Could not map the output file!\n");
            printf("%s\n", strerror(errno));
          }
        }
        else
        {
          printf("Could not map the input file!\n");
          printf("%s\n", strerror(errno));
        }

        fclose(o_file_ptr);
      }
      else
      {
        printf("Could not open the output file!\n");
      }
    }

    fclose(i_file_ptr);
  }
  else
  {
    printf("Could not open the input file!\n");
  }

  return 0;
}
