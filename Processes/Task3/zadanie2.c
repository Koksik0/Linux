#define _POSIX_SOURCE
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
char poczatek[] = "./";
char calosc[100];
char NrSygnalu[100];
char NrMetody[100];
pid_t potomny;
int main(int narg, char *argv[])
{
  strcpy(calosc,poczatek);
  strcat(calosc,argv[1]);
   strcpy(NrMetody,argv[2]);
    strcpy(NrSygnalu,argv[3]);
    
  printf("Id procesu macierzystego: %u\n",getpid());

  switch(fork())
  {
  case -1:
    perror("fork error");
    exit(1);
  case 0:
    potomny = getpid();
    printf("Udało utworzyć się proces potomny\n");
    execlp(calosc,argv[1],NrMetody,NrSygnalu,NULL);
    perror(calosc);
    _exit(2);
  default:
    if(kill(potomny,0)==-1)
      {
	perror("Nie ma takiego procesu\n");
	exit(1);
      }
    sleep(5);
    kill(potomny,NrSygnalu);
    if(wait(NULL)==-1)
      {
	perror("wait error");
	exit(1);
      }
  }
  return 0;
}
