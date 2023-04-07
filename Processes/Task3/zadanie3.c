#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
char poczatek[] = "./";
char calosc[100];
char dalej[100];
char NrSygnalu[100];
char NrMetody[100];
pid_t lider;
int main(int narg, char *argv[])
{
   strcpy(calosc,poczatek);
  strcat(calosc,argv[1]);
  strcpy(dalej,argv[2]);
   strcpy(NrMetody,argv[3]);
    strcpy(NrSygnalu,argv[4]);
    
    switch(lider = fork())
    
    {
    case -1:
    perror("fork error");
    exit(1);
    case 0:
    setpgid(0,0);
    execlp(calosc,argv[1],dalej,NrMetody,NrSygnalu,NULL);    
    perror(calosc);
    _exit(2);
    default:
      if(kill(lider,0)==-1)
	{
	  printf("Brak procesu!!!\n");
	  exit(0);
	}
      	sleep(2);
	kill(-lider,NrSygnalu);
      if(wait(NULL)==-1)
	{
	  perror("Błąd wait");
	  exit(1);
	}
    }
 
  return 0;
}
