#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>

char potok[20];
int stat_lock;
char sciezka[100] = "./";
void wyjscie(void) 
{
	if(unlink (potok)==-1)
	{
		perror("Błąd unlink");
		exit(EXIT_FAILURE);
	}
}
void sygnal_wyjscie(int signal) 
{
	printf ("Usuwanie potoku\n");
	exit(EXIT_FAILURE);
}
int main (int narg, char *argv[]) 
{
	
	strcpy (potok, argv[5]);
	
	if (narg != 6) 
    {
		printf ("Błąd: niepoprawna liczba argumentów!\n");
		exit (EXIT_FAILURE);
	}
	if (mkfifo(argv[5], 0644) == -1) 
    {
		perror("Błąd potoku");
		exit (EXIT_FAILURE);
	}
	if (atexit (wyjscie) != 0) 
    {
		perror("atexit error");
		exit(EXIT_FAILURE);
	}
	if (signal (SIGINT,sygnal_wyjscie) == SIG_ERR) 
    {
		perror("Błąd signal");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < 2; i++) 
    {
		switch (fork ()) 
        {
			case -1:
				perror("fork error");
				exit(EXIT_FAILURE);
			case 0:
				if (i == 0) 
                {
					char temp[100];
					strcpy(temp,sciezka);
					strcat(temp,argv[1]);
					execl (temp, argv[1], argv[3], argv[5], NULL);
				} 
                else 
                {
					char temp[100];
					strcpy(temp,sciezka);
					strcat(temp,argv[2]);
					execl (temp, argv[2], argv[4], argv[5], NULL);
				}
				break;	
			default:
				break;	
		}
	}
	if (wait (&stat_lock) == -1) 
	{
		perror ("Błąd wait");
		exit (EXIT_FAILURE);
	}
	if (wait (&stat_lock) == -1) 
	{
		perror ("Błąd wait");
		exit (EXIT_FAILURE);
	}
	
	return 0;
}