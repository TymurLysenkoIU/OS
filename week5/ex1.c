#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void* thread_fun(void* _)
{
  printf("Hello form thread %lu\n", pthread_self());

  pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
  unsigned long num_threads = 10UL;

  if (argc > 1)
  {
    char* last_char = &(argv[1][strlen(argv[1])]);
    num_threads = strtoul(argv[1], &last_char, 10);
  }

  for (unsigned long i = 0; i < num_threads; ++i)
  {
    pthread_t tid;
    printf("Creating thread %lu...\n", i);

    if (pthread_create(&tid, NULL, thread_fun, NULL))
    {
      printf("Could not create thread %ul!\n", i);
    }

    pthread_join(tid, NULL);
  }

  return 0;
}
