#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
{
  printf("PID: %u  PPID: %u  PGID: %u\n",getpid(),getppid(),getpgid(getpid()));
  sleep(5);
  for(int x=0;x<3;x++)
    {
      pid_t pid = fork();
      if(pid==-1)
	{
	  perror("Fork error");
	  exit(1);
	}
      if(pid==0)
	{
	 
	  printf("PID: %u  PPID: %u  PGID: %u\n",getpid(),getppid(),getpgid(getpid()));
	}
      else
	{
	}
      sleep(5);
    }
}
