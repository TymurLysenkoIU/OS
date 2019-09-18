// Producer consumer with no synchronization according to task

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 100

int _buff[BUFF_SIZE] = {0};
size_t _buff_size = 0;

char _producer_sleep = 0;
char _consumer_sleep = 0;

void* producer(void* _)
{
  while (1)
  {
    while (_producer_sleep);

    if (_buff_size == BUFF_SIZE)
    {
      printf("[Producer] A buffer is full, producer goes to sleep...\n");
      _producer_sleep = 1;
    }
    else
    {
      int new_val = rand() % 100;
      printf("[Producer] Buffer size: %d\n", _buff_size);
      printf("[Producer] Producing: %d\n", new_val);
      _buff[_buff_size++] = new_val;
      _consumer_sleep = 0;
    }
  }

  pthread_exit(NULL);
}

void* consumer(void* _)
{
  while (1)
  {
    while (_consumer_sleep);

    if (_buff_size == 0)
    {
      printf("[Consumer] A buffer is empty, consumer goes to sleep...\n");
      _consumer_sleep = 1;
    }
    else
    {
      printf("[Consumer] Buffer size: %d\n", _buff_size);
      printf("[Consumer] Consuming %d\n", _buff[--_buff_size]);
      _producer_sleep = 0;
    }
  }

  pthread_exit(NULL);
}

int main()
{
  pthread_t producer_tid, consumer_tid;

  pthread_create(&producer_tid, NULL, producer, NULL);
  pthread_create(&consumer_tid, NULL, consumer, NULL);

  pthread_join(consumer_tid, NULL);
  return 0;
}
