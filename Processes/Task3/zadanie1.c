#define _POSIX_SOURCE
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
extern const char * const sys_siglist[];
  int NrMetody, NrSygnalu;
void my_sighandler()
{
  printf("Numer sygnału %d, Nazwa sygnału: %s\n",NrSygnalu,sys_siglist[NrSygnalu]);
}
int main(int narg, char *argv[])
{
  //  printf("PID: %u  Nazwa sygnału: %s\n",getpid(),sys_siglist[NrSygnalu]);

  sscanf(argv[1],"%d",&NrMetody);
  sscanf(argv[2],"%d",&NrSygnalu);
    printf("PID: %u\n",getpid());

    
  if(NrMetody==1)
    {
      kill(getpid(),NrSygnalu);
    }
  else if(NrMetody==2)
    {
      if(signal(NrSygnalu,SIG_IGN)==SIG_ERR)
	{
	  perror("Funkcja signal ma problem z sygnałem");
	  exit(EXIT_FAILURE);
	}
      else
	{
	  printf("Pomyślnie zignorowano sygnał\n");
	}
    }
  else if(NrMetody==3)
    {
      if(signal(NrSygnalu,my_sighandler)==SIG_ERR)
	{
	  perror("Funkcja signal ma problem z sygnałem");
	  exit(EXIT_FAILURE);
	}
      else
	{
	  my_sighandler();
	  exit(0);

	}
    }
  else
    {
      perror("Nieznana metoda");
      exit(0);
    }

  pause();
  return 0;
}
