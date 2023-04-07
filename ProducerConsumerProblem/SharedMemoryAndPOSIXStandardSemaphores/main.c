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
#include "pamiecDzielona.h"
#include "semafory.h"

char nazwaSemaforProducent[20];
char nazwaSemaforKonsument[20];
char nazwaPamieciDzielonej[20];
char sciezka[20];

//funkcja wyjście odpowiada za usunięci pamięci dzielonej i semaforów
void wyjscie() 
{
	usunPamiecDzielona(nazwaPamieciDzielonej);
	usunSemafor(nazwaSemaforProducent);
	usunSemafor(nazwaSemaforKonsument);
}

void sygnalWyjscie(int signal) 
{
	printf("Sygnał przerwania, usuwanie semaforów i pamięci dzielonej");
	exit(EXIT_SUCCESS);
}


int main (int argc, char *argv[]) 
{
	int pamiecDzielona;
	int status;
	sem_t *semaforKonsument;
	sem_t *semaforProducent;
	int wartoscSemafora;
	// sprawdzenie poprawności argumentów
	if(argc != 8) 
    {
		printf ("Niepoprawna liczba argumentów!\n");
		exit (EXIT_FAILURE);
	}
	strcpy(nazwaSemaforProducent,argv[5]);
	strcpy(nazwaSemaforKonsument,argv[6]);
	strcpy(nazwaPamieciDzielonej,argv[7]);
	//Tworzenie semaforów producenta i konsumenta
	semaforProducent = stworzSemafor(nazwaSemaforProducent, NBUF);
	wartoscSemafor(semaforProducent, &wartoscSemafora);
	printf("Utworzono semafor %s (%p) o wartości %d\n", nazwaSemaforProducent, (void *)semaforProducent, wartoscSemafora);
	semaforKonsument = stworzSemafor(nazwaSemaforKonsument, 0);
	wartoscSemafor(semaforKonsument, &wartoscSemafora);
	printf("Utworzono semafor %s (%p) o wartości %d\n", nazwaSemaforKonsument, (void *)semaforKonsument, wartoscSemafora);
	//Tworze pamięć dzieloną
	pamiecDzielona= stworzPamiecDzielona(nazwaPamieciDzielonej);
	ustawRozmiarPamieciDzielonej (pamiecDzielona, sizeof(SegmentPD));
	printf("Utworzono pamięć dzieloną %s o deskryptorze %d i rozmiarze %ld\n\n\n", nazwaPamieciDzielonej, pamiecDzielona, sizeof(SegmentPD));
	
	if (atexit(wyjscie) != 0) 
    {
		perror("atexit error");
		_exit(EXIT_FAILURE);
	}
	//obsługa cirl+C
	if (signal(SIGINT,sygnalWyjscie) == SIG_ERR) 
    {
		perror("Błąd signal");
		exit(EXIT_SUCCESS);
	}
	
	for (int i = 0; i < 2; i++) 
    {
		
		switch (fork()) 
        {
			case -1:
				perror("fork error");
				exit(EXIT_FAILURE);
			case 0:
				//Wywołanie programu producenta
				if (i == 0) 
                {
					strcpy(sciezka,"./");
					strcat(sciezka,argv[1]);
					execl(sciezka, argv[1], nazwaSemaforProducent, nazwaSemaforKonsument, nazwaPamieciDzielonej, argv[3], NULL);
					perror("błąd execl");
					exit (EXIT_FAILURE);
				} 
				//wywołanie programu konsumenta
                else 
                {
					strcpy(sciezka,"./");
					strcat(sciezka,argv[2]);
					execl (sciezka, argv[2], nazwaSemaforProducent, nazwaSemaforKonsument, nazwaPamieciDzielonej, argv[4], NULL);
					perror ("błąd execl");
					exit (EXIT_FAILURE);
				}
				
			default:
				break;	
		}
	}
	// Oczekiwanie na procesy potomne
	for(int x = 0;x<2;x++)
	{
		if (wait (&status) == -1) 
		{
			perror ("Błąd wait");
			_exit (EXIT_FAILURE);
		}
	}
	//Zamykanie pamięci dzielonej
	zamknijPamiecDzielona(pamiecDzielona);
	
	return 0;
}