#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
{
  printf("Id procesu macierzystego: %u\n",getpid());
  printf("Id grupy procesu macierzystego: %u\n",getpgid(getpid()));
  printf("Id użytkownika: %u\n",getuid());
  printf("Id grupy użytkownika: %u\n\n",getgid());
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
	  pid_t zmienna = getpid();
	  printf("Udało się utworzyć proces potomny\n");
	  printf("Id procesu: %u\n",zmienna);
	  if(setpgid(0,0)==-1)
	    {
	      perror("Błąd funkcji setpgid");
	      exit(1);
	    }
	  printf("Id grupy: %u\n",getpgid(zmienna));
	  printf("Id procesu macierzystego: %u\n",getppid());
	  printf("Id uzytkownika: %u\n",getuid());
	  printf("Id uzytkownika grupy: %u\n\n",getgid());
	}
      else
	{
	  if(wait(NULL)==-1)
	    {
	      perror("Błąd przy wait");
	      exit(1);
	    }
	
	}
    }
}
