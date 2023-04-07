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
#include "semafory.h"
#include "pamiecDzielona.h"
int main (int argc, char *argv[]) 
{
	
	int plik;
	int pamiecDzielona;
	SegmentPD *segmentPamieciDzielonej;
	sem_t *semaforProducent;
	sem_t *semaforKonsument;
	int odczyt;
	int wartoscSemafora;
	char ileBajtow[20];
	int czy = 1;
	// sprawdzenie poprawności argumentów
	if (argc != 5) 
	{
		printf ("Niepoprawna liczba argumentów!\n");
		exit (EXIT_FAILURE);
	}
	printf("Producent:\n");
	//Otwieranie procesu producenta i konsumenta
	semaforProducent = otworzSemafor (argv[1]);
	printf ("%s (%p)\n", argv[1], (void *)semaforProducent);
	semaforKonsument = otworzSemafor (argv[2]);
	printf ("%s (%p)\n", argv[2], (void *)semaforKonsument);
	
	pamiecDzielona = otworzPamiecDzielona (argv[3]);
	printf ("Pamięć dzielona: %s deskryptor %d\n", argv[3], pamiecDzielona);
	//Odwzorowywanie pamięci dzielonej
	segmentPamieciDzielonej = (SegmentPD *) odwzorujPamiecDzielona (pamiecDzielona, sizeof(SegmentPD));
	//Ustawienie wstawiania na 0
	segmentPamieciDzielonej->wstaw = 0;
	

	//Otwieram plik do czytania
	if ((plik = open (argv[4], O_RDONLY, 0644)) == -1) 
	{
		printf ("Błąd otwarcia pliku %s do odczytu 1\n", argv[4]);
		perror ("Błąd pliku");
		exit (EXIT_FAILURE);
	}
	//Zapisywanie wyprodukowanych produktów do pamięci dzielonej
	while (czy) 
	{
		
		//Czekaj losową ilość czasu
		sleep (rand()%2);
		
		//Opuszczanie semafora
		wartoscSemafor(semaforProducent, &wartoscSemafora);
		printf ("Producent: przed SK semafor: %d\n", wartoscSemafora);
		opuscSemafor (semaforProducent);
		
		odczyt = read(plik, segmentPamieciDzielonej->bufor[segmentPamieciDzielonej->wstaw], NELE);
		if (odczyt == -1) 
		{
			printf("Błąd odczytu z pliku\n");
			exit(EXIT_FAILURE);
		} 
		//Jeżeli rozmiar się nie zgadza to dodajemy na koniec \0
		if (odczyt != NELE) 
		{
			//Wstawienie na koniec \0
			segmentPamieciDzielonej->bufor[segmentPamieciDzielonej->wstaw][odczyt] = '\0';
			podniesSemafor (semaforKonsument);
			wartoscSemafor(semaforKonsument, &wartoscSemafora);
			printf ("Producent: po SK semafor: %d\n", wartoscSemafora);
			czy = 0;
		} 
		else 
		{
			if(write (1, "Produkuje: (", 12) == -1) 
			{
				perror("Błąd write na ekran");
				exit(EXIT_FAILURE);
			}
			sprintf (ileBajtow, "%ld",strlen(segmentPamieciDzielonej->bufor[segmentPamieciDzielonej->wstaw]));
            if(write(1,ileBajtow,3)==-1)
            {
                perror("Błąd 3 P");
                exit(0);
            }
			if(write (1, ") ", 2) == -1) 
			{
				perror("Błąd write na ekran");
				exit(EXIT_FAILURE);
			}
			if(write (1, segmentPamieciDzielonej->bufor[segmentPamieciDzielonej->wstaw], NELE) == -1) 
			{
				perror("Błąd write na ekran");
				exit(EXIT_FAILURE);
			}
		}
		//Przesuwam kolejność wstawiania o 1
		segmentPamieciDzielonej->wstaw = (segmentPamieciDzielonej->wstaw + 1) % NBUF;
		
		// podnieś semafor konsumenta
		podniesSemafor (semaforKonsument);
		wartoscSemafor(semaforKonsument, &wartoscSemafora);
		printf ("Producent: po SK semafor: %d\n", wartoscSemafora);
	}
	
	if (close (plik) == -1) 
	{
		perror ("Błąd zamknięcia pliku wyjścia");
		exit (EXIT_FAILURE);
	}
	
	usunOdwzorowaniePamieciDzielonej(segmentPamieciDzielonej, sizeof(SegmentPD));
	zamknijPamiecDzielona (pamiecDzielona);
	zamknijSemafor(semaforProducent);
	zamknijSemafor(semaforKonsument);	
	return 0;
}