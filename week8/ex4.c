#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int main()
{
  for (int i = 0; i < 10; ++i)
  {
    calloc(sizeof(char), 1024 * 1024 * 10);
    
    struct rusage mem;
    if (getrusage(RUSAGE_SELF, &mem))
    {
      printf("An error occured while trying to get info about memory usage.\n");
    }
    else
    {
      printf(
        "User CPU time used: %lld sec\n"
        "User CPU time used: %lld \n"
        "System CPU time used: %lld \n"
        "Maximum resident set size: %lld \n"
        "Integral shared memory size: %lld \n"
        "Integral unshared data size: %lld \n"
        "Integral unshared stack size: %lld \n"
        "Page reclaims (soft page faults): %lld \n"
        "Page faults (hard page faults): %lld \n"
        "Swaps: %lld \n"
        "Block input operations: %lld \n"
        "Block output operations: %lld \n"
        "Ipc messages sent: %lld \n"
        "Ipc messages received: %lld \n"
        "Signals received: %lld \n"
        "Voluntary context switches: %lld \n"
        "Involuntary context switches: %lld \n"
        "System CPU time used: %lld \n"
        "\n\n",
        mem.ru_utime.tv_sec,
        mem.ru_stime.tv_sec,
        mem.ru_maxrss,
        mem.ru_ixrss,
        mem.ru_idrss,
        mem.ru_isrss,
        mem.ru_minflt,
        mem.ru_majflt,
        mem.ru_nswap,
        mem.ru_inblock,
        mem.ru_oublock,
        mem.ru_msgsnd,
        mem.ru_msgrcv,
        mem.ru_nsignals,
        mem.ru_nvcsw,
        mem.ru_nivcsw
      );
    }

    sleep(1);
  }

  return 0;
}
