#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

void execute_command(const char* restrict command, const char* (*const arguments)[])
{
  pid_t pid = fork();

  if (pid == 0)
  {
    execv(command, *arguments);
    exit(0);
  }
  else if (pid < 0)
  {
    printf("Error forking shell\n");
  }
  else
  {
    int status;

    do
    {
      waitpid(pid, &status, 0);
    }
    while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
}

void split_command_arguments(char* line, char** command, char* (**arguments)[], size_t* num_arguments)
{
  char* token = strtok(line, " \n");
  size_t token_size = strlen(token);
  *command = malloc(token_size);
  strncpy(*command, token, token_size);
  command[token_size - 1] = '\0';

  size_t num_args = 0;
  token = strtok(NULL, " \n");
  *arguments = malloc(sizeof(char*));
  while (token != NULL)
  {
    ++num_args;
    *arguments = realloc(*arguments, sizeof(char*) * num_args);
    token_size = strlen(token);
    (**arguments)[num_args - 1] = token;
    // (**arguments)[num_args - 1][token_size - 1] = '\0';
    token = strtok(NULL, " \n");
  }

  if (num_args == 0)
  {
    free(*arguments);
  }
  *num_arguments = num_args;
}

ssize_t prompt(char** input)
{
  printf("[tymash]$ ");
  size_t buffer_size = 0;
  return getline(input, &buffer_size, stdin);
}

int main()
{
  char* input = NULL;
  char* command;
  char* (*arguments)[];
  size_t num_arguments = 0;

  while (1)
  {
    if (input)
    {
      free(input);
      input = NULL;
    }

    prompt(&input);

    if (strcmp(input, "exit\n"))
    {
      split_command_arguments(input, &command, &arguments, &num_arguments);
      execute_command(command, arguments);

      if (num_arguments)
      {
        free(arguments);
      }
    }
    else
    {
      break;
    }
  }
  free(input);

  return 0;
}
