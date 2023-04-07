#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
char poczatek[] = "./";
char calosc[100];
pid_t potomny;
int status;
int main(int narg, char *argv[])
{
  int NrMetody;
  int NrSygnalu;
  strcpy(calosc,poczatek);
  strcat(calosc,argv[1]);
  // setpgid(getpid(),0);
  printf("PID: %u  PGID: %u\n",getpid(),getpgrp());
  sscanf(argv[2],"%d",&NrMetody);
  sscanf(argv[3],"%d",&NrSygnalu);

  if(signal(atoi(argv[2]),SIG_IGN)==SIG_ERR)
	{
	  perror("Funkcja signal ma problem z sygnałem");
	  exit(EXIT_FAILURE);
	}
  else
	{
	  //printf("Pomyślnie zignorowano sygnał\n");
	}
  for(int x  =0;x<3;x++)
    {
  switch(fork())
    {
  case -1:
    perror("Błąd fork");
    exit(1);
   case 0:
     potomny = getpid();
     // printf("PID: %u, PGID: %u\n",getpid(),getpgrp());
     execl(calosc,argv[1],argv[2],argv[3],NULL);
      perror(calosc);
      exit(2);

    };
  
}
  
  for(int x = 0;x<3 ; x++)
    {
      // printf("Wait :%d",wait(&status));
      if(wait(&status)==-1)
      {
	perror("wait error");
	exit(1);
      }
      printf("Stan zakończenia %d\n",status);
	
    }

  
}
