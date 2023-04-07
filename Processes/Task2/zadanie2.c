#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{
  printf("UID: %u ",getuid());
  printf("GID: %u ",getgid());
  printf("PID: %u ",getpid());
  printf("PPID: %u ",getppid());
  printf("PGID: %u\n",getpgid(getpid()));
}
