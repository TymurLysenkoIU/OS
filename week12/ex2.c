#include <sys/stat.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  char do_append = (strcmp(argv[1], "-a") == 0);

  if (
    (argc < 2) ||
    (strcmp(argv[1], "--help") == 0) ||
    ((argc == 2) && do_append)
  )
  {
    printf("%s [-a] <list_of_sinks>\n", argv[0]);
    return 0;
  }

  size_t input_len = 1 * sizeof(char);
  size_t chars_read = 0;
  char* input = malloc(input_len);
  char cur_char;
  while ((cur_char = getchar()) != EOF)
  {
    if ((chars_read + 1) > input_len)
    {
      input_len *= 2;
      input = realloc(input, input_len);
    }

    input[chars_read++] = cur_char;
  }
  printf("%s", input);

  mode_t file_perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
  for (size_t i = ((do_append) ? 2 : 1); i < argc; ++i)
  {
    int open_flags = O_WRONLY | ((do_append) ? O_APPEND : O_CREAT) | ((do_append) ? 0 : O_TRUNC);
    int file_d = open(argv[i], open_flags, file_perms);

    if (file_d == -1)
    {
      printf("Did not manage to write to %s", argv[i]);
    }
    else
    {
      write(file_d, input, chars_read);
      close(file_d);
    }
  }

  free(input);
  return 0;
}
