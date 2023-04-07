#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
{
  printf("Id procesu macierzystego: %u\n\n",getpid());
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
	  printf("Udało się utworzyć proces potomny\n");
	  printf("Id procesu: %u\n",getpid());
	  printf("Id grupy: %u\n",getpgid(getpid()));
	  printf("Id procesu macierzystego: %u\n",getppid());
	  printf("Id użytkownika: %u\n",getuid());
	  printf("Id uzytkownika grupy: %u\n\n",getgid());
	  if(x==2)
	    {
	      sleep(40);
	    }
	}
    else
      {
	  if(x==2)
	    {
	      exit(0);
	    }
	}
	
    }
}
