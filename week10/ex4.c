#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef
  struct
  {
    __ino_t inode;
    char* file_names[1024];
    size_t num_files;
  }
repeated_dirent;

int main(int argc, char* argv[])
{
  if (argc > 1)
  {
    DIR* target;
    if (target = opendir(argv[1]))
    {
      FILE* output_file = stdout;

      if (argc > 2)
      {
        if (!(output_file = fopen(argv[2], "a")))
        {
          printf("An error occured while trying to create the output file. Outputting to stdout...\n");
          output_file = stdout;
        }
      }

      struct dirent* cur_ent = NULL;
      repeated_dirent repeated_entries[512] = { 0 };

      while (cur_ent = readdir(target))
      {
        repeated_dirent* cur_repeated_ent = repeated_entries;

        while (cur_repeated_ent->inode && (cur_repeated_ent->inode != cur_ent->d_ino))
        {
          ++cur_repeated_ent;
        }

        cur_repeated_ent->inode = cur_ent->d_ino;
        strcpy(
          cur_repeated_ent->file_names[cur_repeated_ent->num_files] = malloc(256),
          cur_ent->d_name
        );
        ++(cur_repeated_ent->num_files);
      }

      closedir(target);

      repeated_dirent* cur_repeated_ent = repeated_entries;
      while (cur_repeated_ent->inode)
      {
        if (cur_repeated_ent->num_files > 1)
        {
          fprintf(
            output_file,
            "Inode: %lu\n"
            "\tFilenames:\n",
            cur_repeated_ent->inode
          );

          for (size_t i = 0; i < cur_repeated_ent->num_files; ++i)
          {
            fprintf(
              output_file,
              "\t\t%s\n",
              cur_repeated_ent->file_names[i]
            );
          }
          fprintf(output_file, "\n");
        }

        ++cur_repeated_ent;
      }

      fclose(output_file);
    }
    else
    {
      printf("An error occured while trying to open the provided directory.\n");
    }
  }
  else
  {
    printf("Please, provide a path to a directory as the first argument.\n");
  }

  return 0;
}
