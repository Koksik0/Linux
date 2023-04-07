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

int main (int narg, char *argv[]) 
{
	
	char bufor[1024];
	int plik;
	int potok;
	int odczyt;
	int rozmiarDanychProducent = 20;
	char wypisz[20+rozmiarDanychProducent];
    char ileBajtow[100];
	
	if (narg != 3) 
    {
		printf ("Błąd: niepoprawna liczba argumentów!\n");
		exit (EXIT_FAILURE);
	}
	
	srand(time(NULL));
	
	if ((plik = open (argv[1], O_RDONLY, 0644)) == -1) 
    {
		printf ("Błąd otwarcia pliku %s do odczytu\n", argv[1]);
		perror ("Błąd pliku");
		exit (EXIT_FAILURE);
	}
	
	if ((potok = open (argv[2], O_WRONLY, 0644)) == -1) 
    {
		printf ("Błąd otwarcia potoku %s do odczytu\n", argv[2]);
		perror ("Błąd pliku");
		exit (EXIT_FAILURE);
	}
	while (1) 
    {
		sleep(rand()%5);
		
		odczyt = read(plik, &bufor, rozmiarDanychProducent);
		if (odczyt == -1) 
        {
			printf("Błąd odczytu z pliku\n");
			exit(EXIT_FAILURE);
		} 
        else if (odczyt == 0) 
        {
			break;
		} 
        else 
        {
			if(write (potok, &bufor, odczyt) == -1)
            {
				perror("Błąd write do potoku");
				exit(EXIT_FAILURE);
			}
			 if(write(1,"Bajty z pliku: ",15)==-1)
            {
                perror("Błąd 2 M");
                exit(0);
            }
            sprintf (ileBajtow, "%d",odczyt);
            if(write(1,ileBajtow,3)==-1)
            {
                perror("Błąd 3 M");
                exit(0);
            }
            if(write(1,"\n",2)==-1)
            {
                perror("Błąd 4 M");
                exit(0);
            }
			bufor[odczyt] = '\0';
            strcpy(wypisz,"Produkuje: ");
            strcat(wypisz,bufor);
            strcat(wypisz,"\n");
            if(write(1,wypisz,sizeof(wypisz))==-1)
            {
                perror("Błąd 5 M");
                exit(0);
			}
		}
	}
	
	if (close (plik) == -1) 
    {
		perror ("Błąd zamknięcia pliku wyjścia");
		exit (EXIT_FAILURE);
	}
	
	if (close (potok) == -1) 
    {
		perror ("Błąd zamknięcia potoku");
		exit (EXIT_FAILURE);
	}
	
	return 0;
}