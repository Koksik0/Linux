#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include "semafory.h"
#include <time.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

char nazwaSemafora[20];
int status;
int iloscProcesow;
int plik;
char sciezkaDoWzajemneWykluczanie[30];
int wartoscSemafora;
int odczyt;
char bufor[10];
void wyjscie(void) 
{
	usunSemafor(nazwaSemafora);
}

void sygnalWyjscie(int signal) 
{
	printf("Pomyślnie przerwano program\n");
	usunSemafor(nazwaSemafora);
	_exit(EXIT_SUCCESS);
}
int main(int argc, char *argv[]) 
{
	
	//Sprawdzenie poprawności argumentów wywołania programu
	if(argc != 6) 
	{
		printf("Błąd: niepoprawna liczba argumentów!\n");
		printf("Wywołaj program wpisując: %s program iloscProcesów iloscSekcjiKrytycznych plik nazwaSemafora \n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	//Obsługa atexit
	if(atexit(wyjscie) != 0) 
	{
		perror("atexit error");
		exit(EXIT_FAILURE);
	}
	
	//Obsługa sygnału ctrl+c
	if(signal(SIGINT, sygnalWyjscie) == SIG_ERR) 
	{
		perror("Błąd signal");
		exit(EXIT_FAILURE);
	}
	//Pobieranie danych z argumentów wywołania programu
	iloscProcesow = atoi(argv[2]);
	strcpy(nazwaSemafora, argv[5]);
	strcpy(sciezkaDoWzajemneWykluczanie,"./");
	strcat(sciezkaDoWzajemneWykluczanie,argv[1]);
	
	//Zapis do pliku początkowej wartości - 0
	if((plik = open (argv[4], O_WRONLY | O_CREAT, 0644)) == -1) 
	{
		printf("Błąd otwarcia pliku %s do zapisu", argv[1]);
		perror("Błąd pliku");
		exit(EXIT_FAILURE);
	}
	
	if(write(plik, "0", 2) == -1)
	{
		perror("Błąd write do pliku");
		exit(EXIT_FAILURE);
	}
	
	if(close(plik) == -1) 
	{
		perror ("Błąd zamknięcia pliku");
		exit (EXIT_FAILURE);
	}

	//Tworzenie semafora, wypisywanie wartości semafora
	sem_t *semafor = stworzSemafor(nazwaSemafora);
	wartoscSemafor(semafor, &wartoscSemafora);
	printf("Utworzono semafor %s (%p) o wartości %d\n", nazwaSemafora, (void *)semafor, wartoscSemafora);


	//Wywołanie programu wzajemneWykluczenie.c określoną ilość razy
	for(int i = 0; i < iloscProcesow; i++) 
	{
		
		switch(fork()) 
		{
			case -1:
				perror("fork error");
				exit(EXIT_FAILURE);
			case 0:
				//wywołanie wzajemneWykluczanie.c, a także przekazanie argumentów wywołania programu
				execl(sciezkaDoWzajemneWykluczanie, argv[1], argv[3], argv[4], argv[5], argv[6], NULL);
				perror("execl error");
				exit(EXIT_FAILURE);
				break;
			default:
				break;
				
		}
	}
	
	// Oczekiwanie na zakończenie procesów potomnych
	for(int i = 0; i < iloscProcesow; i++) 
	{
		if(wait(&status) == -1) 
		{
			perror("Błąd wait");
			exit(EXIT_FAILURE);
		}
	}
	//Otwieramy plik, aby odczytac końcową wartość w pliku
	if((plik = open(argv[4], O_RDONLY, 0644)) == -1) 
	{
		printf("Błąd otwarcia pliku %s do odczytu", argv[4]);
		perror("Błąd pliku");
		exit(EXIT_FAILURE);
	}
	
	odczyt = read(plik, &bufor, 10);
	if(odczyt == -1) 
	{
		printf("Błąd odczytu z pliku\n");
		exit(EXIT_FAILURE);
	} 
	else if(odczyt == 0) 
	{
		printf("Plik jest pusty! Coś poszło nie tak!\n");
		exit(EXIT_FAILURE);
	} 
	else 
	{
		if(atoi(bufor) == (atoi(argv[2]) * atoi(argv[3]))) 
		{
			printf("\nPomyślne zakończenie! Liczba w pliku: %s\n", bufor);
		} 
		else 
		{
			printf("\nNie udało się! Liczba w pliku: %s, powinno być: %d\n", bufor, (atoi(argv[2]) * atoi(argv[3])));
		}
	}
	//Zamykanie pliku
	if(close(plik) == -1) 
	{
		perror("Błąd zamknięcia pliku");
		exit(EXIT_FAILURE);
	}
	
	return 0;
}