#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
char poczatek[] = "./";
char calosc[100];
int main(int narg, char *argv[])
{
  strcpy(calosc,poczatek);
  strcat(calosc,argv[1]);
  printf("Id procesu macierzystego: %u\n\n",getpid());
  for(int x = 0; x<3; x++)
    {
  switch(fork())
  {
  case -1:
    perror("fork error");
    exit(1);
  case 0:
    printf("Udało utworzyć się proces potomny\n");
    execlp(calosc,argv[1],"",NULL);
    perror(calosc);
    _exit(2);
  default:
     if(wait(NULL)==-1)
	    {
	      perror("Błąd wait");
	      exit(1);
	    }
  }
  if(x!=2)
    {
  printf("\n");
    }
    }
    
}
