#define NELE 10 // Rozmiar elementu bufora (jednostki towaru) w bajtach
#define NBUF 5 // Liczba elementow bufora
// Segment pamieci dzielonej
typedef struct 
{
	char bufor[NBUF][NELE]; // Wspolny bufor danych
	int wstaw;
	int wyjmij;
} SegmentPD;
int stworzPamiecDzielona(const char *);
int otworzPamiecDzielona(const char *);
void ustawRozmiarPamiecyDzielonej(int, off_t);
void zamknijPamiecDzielona(int);
void usunPamiecDzielona(const char *);
void *odwzorujPamiecDzielona(int, size_t);
void usunOdwzorowaniePamieciDzielonej(void *, size_t);