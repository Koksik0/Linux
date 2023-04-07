#include "kolejkiKomunikatow.h"
char koncowyWynik[maxymalnaDlugosckomunikatu];
void wyjscie(void) 
{
	usunKolejkeKomunikatow(nazwaKolejkiKomunikatow);
}
void sygnalWyjscie(int signal) 
{
	printf("\nSygnał przerwania, usuwanie kolejki\n");
	exit(EXIT_SUCCESS);
}
//Funkcja zwracajaca wynik działania w tablicy char
char *oblicz(int operator, int pierwszaLiczba, int drugaLiczba, char *wyjscie)
{
	int wynik;
	if(operator == '+') 
	{
		wynik = pierwszaLiczba + drugaLiczba;
		sprintf(wyjscie, "%d", wynik);
	} 
	else if(operator == '-') 
	{
		wynik = pierwszaLiczba - drugaLiczba;
		sprintf(wyjscie, "%d", wynik);
	} 
	else if(operator == '*') 
	{
		wynik = pierwszaLiczba * drugaLiczba;
		sprintf(wyjscie, "%d", wynik);
	} 
	else if(operator == '/') 
	{
		wynik = pierwszaLiczba / drugaLiczba;
		sprintf(wyjscie, "%d", wynik);
	} 
	else 
	{
		sprintf(koncowyWynik, "Błąd: nieznany operator");
	}
	return wyjscie;
}

int main() 
{
	int PIDKlienta;
	char daneDoDzialaniaOdKlienta[maxymalnaDlugosckomunikatu];
	int pierwszaLiczba;
	int drugaLiczba;
	char operator;
	mqd_t kolejkaKlienta;
	mqd_t wyslijOdpowiedz;
	//Tworzenie kolejki, wraz z wypisaniem argumentów
	kolejkaKlienta = stworzKolejkeKomunikatow(nazwaKolejkiKomunikatow,O_RDONLY,1);

	//Obsługa atexit
	if(atexit(wyjscie) != 0) 
	{
		perror("atexit error");
		exit(EXIT_FAILURE);
	}
	//Obsługa ctrl+c
	if(signal(SIGINT,sygnalWyjscie) == SIG_ERR) 
	{
		perror("Błąd signal");
		exit(EXIT_FAILURE);
	}
	
	while(1) 
	{
		//Odbierz dane do działania od klienta
		odbierzZKolejkikomunikatow(kolejkaKlienta, daneDoDzialaniaOdKlienta, NULL);
		//Zczytaj dane do działania od klienta
		sscanf(daneDoDzialaniaOdKlienta, "%d %d%c%d", &PIDKlienta, &pierwszaLiczba, &operator, &drugaLiczba);
		printf("Zapytanie od %d - działanie %d%c%d\n", PIDKlienta, pierwszaLiczba, operator, drugaLiczba);
		
		//Czekaj losową ilość czasu
		sleep(rand()%2);
		
		//Otwieram kolejke do nadania odpowiedzi
		sprintf(daneDoDzialaniaOdKlienta, "/%d", PIDKlienta);
		wyslijOdpowiedz = otworzKolejkeKomunikatow(daneDoDzialaniaOdKlienta, O_WRONLY,1);

		//Wyślij odpowiedź do klienta, zamknij kolejke
		printf("Wysyłanie odpowiedzi %s do procesu %d\n", oblicz(operator,pierwszaLiczba,drugaLiczba,koncowyWynik), PIDKlienta);
		wyjslijDoKolejkiKomunikatow(wyslijOdpowiedz, oblicz(operator,pierwszaLiczba,drugaLiczba,koncowyWynik),1);
		zamknijKolejkeKomunikatow(wyslijOdpowiedz);
	}
	//Usuń kolejke komunikatów
	usunKolejkeKomunikatow(nazwaKolejkiKomunikatow);
	return 0;
}