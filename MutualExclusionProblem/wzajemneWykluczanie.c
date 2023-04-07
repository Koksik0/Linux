#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include "semafory.h"
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int odczyt;
char bufor[100];
int liczba;
int iloscSekcjiKrytycznych;
sem_t *semafor;
int wartoscSemafora;
int plik;
int main (int argc, char *argv[]) 
{
	
	if(argc != 4) 
	{
		printf("Niepoprawna liczba argumentów!\n");
		printf("Wywołaj podprogram wpisując: %s iloscSekcjiKrytycznych plik nazwaSemafora\n", argv[0]);
		_exit(EXIT_FAILURE);
	}
	
	//Pobieranie danych z argumentów wywołania programu
	
	iloscSekcjiKrytycznych = atoi(argv[1]);
	semafor = otworzSemafor(argv[3]);
	
	for(int i = 0; i < iloscSekcjiKrytycznych; i++) 
	{
		//Czekamy losową ilość czasu
		sleep(rand()%2);
		
		//Opuszczanie semafora
		wartoscSemafor(semafor, &wartoscSemafora);
		opuscSemafor(semafor);
		printf("PID %d przed SK semafor: %d\n", getpid(), wartoscSemafora);
		//Sekcja Krytyczna
		//Otwieramy plik tylko do odczytu, odczytujemy z niego aktualną wartość w pliku, następnie zamykamy plik
		if((plik = open (argv[2], O_RDONLY, 0644)) == -1) 
		{
			printf ("Błąd otwarcia pliku %s do odczytu", argv[2]);
			perror ("Błąd pliku");
			_exit (EXIT_FAILURE);
		}
		
		odczyt = read(plik, &bufor, 10);
		if(odczyt == -1) 
		{
			printf("Błąd odczytu z pliku\n");
			_exit(EXIT_FAILURE);
		} 
		else if(odczyt == 0) 
		{
			printf("Nie odczytano żadnych danych\n");
			break;
		} 
		else 
		{
			wartoscSemafor(semafor, &wartoscSemafora);
			printf("	PID: %d, semafor %d, odczytany numer: %s, numer SK: %d",getpid(),wartoscSemafora,bufor,i);
		}
		//Zamknięcie pliku
		if(close (plik) == -1) 
		{
			perror("Błąd zamknięcia pliku");
			exit(EXIT_FAILURE);
		}
		//Podnosimy liczbę 
		liczba = atoi(bufor);
		liczba++;
		sprintf(bufor, "%d", liczba);
		printf(" Aktualna liczba: %d ", liczba);
		
		//Czekamy losową ilość czasu
		sleep(rand()%2);
		//Otwieramy plik tylko do zapisu, nadpisujemy jego zawartość wcześniej zinkrementowaną wartością, następnie zamykamy plik
		if((plik = open (argv[2], O_WRONLY | O_CREAT, 0644)) == -1) 
		{
			printf("Błąd otwarcia pliku %s do zapisu", argv[1]);
			perror("Błąd pliku");
			_exit(EXIT_FAILURE);
		}
		
		if(write (plik, &bufor, strlen(bufor)) == -1)
		{
			perror("Błąd write do pliku");
			_exit(EXIT_FAILURE);
		}
		//Zamknięcie pliku
		if(close (plik) == -1) 
		{
			perror("Błąd zamknięcia pliku");
			exit(EXIT_FAILURE);
		}

		//Podniesienie semafora, a także wypisanie pid procesu po sekcji krytycznej i wartości semafora
		podniesSemafor (semafor);
		wartoscSemafor(semafor, &wartoscSemafora);
		printf("\nPID %d po SK semafor: %d\n\n", getpid(), wartoscSemafora);
	}
	//Zamykanie semafora
	zamknijSemafor(semafor);
	return 0;
}