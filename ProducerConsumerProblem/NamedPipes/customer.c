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
	int rozmiarDanychKonsument = 10;
	char wypisz[13+rozmiarDanychKonsument];
	char ileBajtow[100];
	if (narg != 3) 
    {
		printf ("Błąd: niepoprawna liczba argumentów!\n");
		printf ("Wywołaj program wpisując: %s plik_wy potok\n", argv[0]);
		exit (EXIT_FAILURE);
	}
	
	if ((plik = open (argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) 
    {
		printf ("Błąd otwarcia pliku %s do zapisu", argv[1]);
		perror ("Błąd pliku");
		exit (EXIT_FAILURE);
	}
	
	if ((potok = open (argv[2], O_RDONLY, 0644)) == -1) 
    {
		printf ("Błąd otwarcia potoku %s do odczytu", argv[2]);
		perror ("Błąd pliku");
		exit (EXIT_FAILURE);
	}
	while (1) 
    {
		sleep(rand()%5);
		
		odczyt = read(potok, &bufor, rozmiarDanychKonsument);
		if (odczyt == -1) 
        {
			printf("Błąd odczytu z potoku\n");
			exit(EXIT_FAILURE);
		} 
        else if (odczyt == 0) 
        {
			break;
		} 
        else 
        {
			if (write (plik, &bufor, odczyt) == -1)
            {
				perror("Błąd write do pliku");
				exit(EXIT_FAILURE);
			}
			if(write(1,"Bajty z potoku: ",16)==-1)
            {
                perror("Błąd 2 P");
                exit(0);
            }
            sprintf (ileBajtow, "%d",odczyt);
            if(write(1,ileBajtow,3)==-1)
            {
                perror("Błąd 3 P");
                exit(0);
            }
            if(write(1,"\n",2)==-1)
            {
                perror("Błąd 4 P");
                exit(0);
            }
			bufor[odczyt] = '\0';
            strcpy(wypisz,"Odebrane: ");
            strcat(wypisz,bufor);
            strcat(wypisz,"\n");
            if(write(1,wypisz,sizeof(wypisz))==-1)
            {
                perror("Błąd 5 P");
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