#include "kolejkiKomunikatow.h"
mqd_t kolejkaSerwera;

void wyjscie(void) 
{
	zamknijKolejkeKomunikatow(kolejkaSerwera);
}

void sygnalWyjscie(int signal) 
{
	printf("\nSygnał przerwania, zamykanie kolejki\n");
	exit(EXIT_SUCCESS);
}

int main() 
{
	char nazwaKolejkiDoOdbierania[10];
	mqd_t wynikDzialania;
	char dzialanieDoWyslania[maxymalnaDlugosckomunikatu];
	char dzialanieDoWyslaniaZPID[maxymalnaDlugosckomunikatu+5];
	char wynikDzialaniaOdebranyOdSerwera[maxymalnaDlugosckomunikatu];
	//Zapisujemy pid procesu, który będzie nazwą kolejki
	sprintf(nazwaKolejkiDoOdbierania, "/%d", getpid());
	
	//Czekamy na serwer
	sleep(5);
	
	//Otwieramy kolejkę stworzoną przez serwer
	kolejkaSerwera = otworzKolejkeKomunikatow(nazwaKolejkiKomunikatow, O_WRONLY,1);
	//Obsługa atexit
	if(atexit(wyjscie) != 0) 
	{
		perror("atexit error");
		_exit(EXIT_FAILURE);
	}
	//Obsługa ctl+c
	if(signal(SIGINT,sygnalWyjscie) == SIG_ERR) 
	{
		perror("Błąd signal");
		exit(EXIT_FAILURE);
	}
	//Czekaj losową ilość czasu
	sleep(rand()%2);
	
	while(1) 
	{
		
		// wpisz działanie
		printf("Działanie:\n");
		if(scanf("%s", dzialanieDoWyslania) == EOF) 
		{
			printf("Koniec\n");
			exit(EXIT_SUCCESS);
		}
		//Dodaj PID procesu
		sprintf(dzialanieDoWyslaniaZPID, "%d %s", getpid(), dzialanieDoWyslania);
		
		//Wyslij działanie na serwer aby je wykonał
		wyjslijDoKolejkiKomunikatow(kolejkaSerwera, dzialanieDoWyslaniaZPID, 1);
		printf("\nZapytanie: %s\n", dzialanieDoWyslaniaZPID);
		
		//Tworzenie kolejki do odbierania odpowiedzi
		wynikDzialania = stworzKolejkeKomunikatow(nazwaKolejkiDoOdbierania, O_RDONLY,1);
		//Odbierz i wyświetl wynik działania
		odbierzZKolejkikomunikatow(wynikDzialania, wynikDzialaniaOdebranyOdSerwera, NULL);
		printf("Odpowiedź z serwera: %s\n\n", wynikDzialaniaOdebranyOdSerwera);
		
		//Zamknij i usuń kolejke
		zamknijKolejkeKomunikatow(wynikDzialania);
		usunKolejkeKomunikatow(nazwaKolejkiDoOdbierania);
		
		//Czekaj losową ilość czasu
		sleep(rand()%2);
	}
	//Zamknij kolejkę
	zamknijKolejkeKomunikatow(kolejkaSerwera);
	return 0;
}