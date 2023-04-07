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
int czyKoniec(SegmentPD *segmantPamieciDzielonej) 
{
	for (int i = 0; i < NELE; i++) 
	{
		if (segmantPamieciDzielonej->bufor[segmantPamieciDzielonej->wyjmij][i] == '\0') 
		{
			return 1;
		}
	}
	return 0;
}

int main (int argc, char *argv[]) 
{
	
	int plik;
	int pamiecDzielona;
	SegmentPD *segmentPamieciDzielonej;
	sem_t *semaforProducent;
	sem_t *semaforKonsument;
	int wartoscSemafora;
	char ileBajtow[20];
	int czy = 1;
	// sprawdzenie poprawności argumentów
	if (argc != 5) 
	{
		printf ("Niepoprawna liczba argumentów!\n");
		exit (EXIT_FAILURE);
	}
	
	if ((plik = open (argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) 
	{
		printf ("Błąd otwarcia pliku %s do zapisu", argv[4]);
		perror ("Błąd pliku");
		exit (EXIT_FAILURE);
	}
	printf("Konsument:\n");
	//Otwieranie semaforów producenta i konsumenta
	semaforProducent = otworzSemafor (argv[1]);
	printf ("%s (%p)\n", argv[1], (void *)semaforProducent);
	semaforKonsument = otworzSemafor (argv[2]);
	printf ("%s (%p)\n", argv[2], (void *)semaforKonsument);

	//Otwieranie pamięci dzielonej
	pamiecDzielona = otworzPamiecDzielona (argv[3]);
	printf ("Pamięć dzielona: %s deskryptor %d\n", argv[3], pamiecDzielona);
	//Odwzorowywanie pamięci dzielonej
	segmentPamieciDzielonej = (SegmentPD *) odwzorujPamiecDzielona (pamiecDzielona, sizeof(SegmentPD));
	
	segmentPamieciDzielonej->wyjmij = 0;
	
	//Zapisywanie skosumowanych produktów do pliku
	while (czy) 
	{
		//Czekaj losową ilość czasu
		sleep (rand()%2);
		
		//Opuść semafor
		wartoscSemafor(semaforProducent, &wartoscSemafora);
		printf ("Konsument: przed SK semafor: %d\n", wartoscSemafora);
		opuscSemafor (semaforKonsument);
		//Jeżeli bufor jest pełny to kopiuj wszystko
		if (!czyKoniec(segmentPamieciDzielonej)) 
		{
			if (write (plik, segmentPamieciDzielonej->bufor[segmentPamieciDzielonej->wyjmij], NELE) == -1) 
			{
				perror("Błąd write do potoku");
				exit(EXIT_FAILURE);
			}
			if(write (1, "		Konsumuje: (", 12) == -1) 
			{
				perror("Błąd write na ekran");
				exit(EXIT_FAILURE);
			}
			sprintf (ileBajtow, "%ld",strlen(segmentPamieciDzielonej->bufor[segmentPamieciDzielonej->wyjmij]));
            if(write(1,ileBajtow,3)==-1)
            {
                perror("Błąd 3 P");
                exit(0);
            }
			if(write (1, " )", 1) == -1) 
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
		else 
		{
			if (write (plik, segmentPamieciDzielonej->bufor[segmentPamieciDzielonej->wyjmij], strlen (segmentPamieciDzielonej->bufor[segmentPamieciDzielonej->wyjmij])) == -1) 
			{
				perror("Błąd write do potoku");
				exit(EXIT_FAILURE);
			}
			podniesSemafor (semaforProducent);
			wartoscSemafor(semaforProducent, &wartoscSemafora);
			printf ("Konsument: po SK semafor: %d\n", wartoscSemafora);
			czy = 0;
		}
		
		segmentPamieciDzielonej->wyjmij = (segmentPamieciDzielonej->wyjmij + 1) % NBUF;
		
		//Podnieś semafor producenta
		podniesSemafor (semaforProducent);
		wartoscSemafor(semaforProducent, &wartoscSemafora);
		printf ("Konsument: po SK semafor: %d\n", wartoscSemafora);
	}
	
	if (close (plik) == -1) 
	{
		perror ("Błąd zamknięcia pliku wyjścia");
		exit (EXIT_FAILURE);
	}
	//Usunięcie odwzorowania
	usunOdwzorowaniePamieciDzielonej(segmentPamieciDzielonej, sizeof(SegmentPD));
	//Zamykanie Pamięci Dzielonej i semaforów
	zamknijPamiecDzielona (pamiecDzielona);
	zamknijSemafor(semaforKonsument);
	zamknijSemafor(semaforProducent);
	
	return 0;
}