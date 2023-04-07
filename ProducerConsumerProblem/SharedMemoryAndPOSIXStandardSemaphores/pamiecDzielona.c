#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int stworzPamiecDzielona (const char *name) 
{
	int deskryptor;
	if ((deskryptor = shm_open(name, O_EXCL | O_RDWR | O_CREAT, 0644)) == -1) 
	{
		perror ("błąd tworzenia pamieci dzielonej");
		exit (EXIT_FAILURE);
	}
	return deskryptor;
}

int otworzPamiecDzielona (const char *name) 
{
	int deskryptor;
	if ((deskryptor = shm_open(name, O_RDWR, 0644)) == -1) 
	{
		perror ("błąd otwierania pamieci dzielonej");
		exit (EXIT_FAILURE);
	}
	return deskryptor;
	
}

void ustawRozmiarPamieciDzielonej (int fd, off_t length) 
{
	if (ftruncate(fd, length) == -1) 
	{
		perror ("błąd inicjowania pamieci dzielonej");
		exit (EXIT_FAILURE);
	}
}

void zamknijPamiecDzielona (int fd) 
{
	if (close(fd) == -1)
	{
		perror ("błąd zamykania pamieci dzielonej");
		exit (EXIT_FAILURE);
	}
}

void usunPamiecDzielona (const char *name) 
{
	if (shm_unlink(name) == -1) 
	{
		perror ("błąd usuwania pamieci dzielonej");
		exit (EXIT_FAILURE);
	}
}

void *odwzorujPamiecDzielona (int fd, size_t length) 
{
	void *adres = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (adres == MAP_FAILED) 
	{
		perror ("błąd odwzorowania pamieci dzielonej");
		exit (EXIT_FAILURE);
	}
	return adres;
	
}

void usunOdwzorowaniePamieciDzielonej (void *addr, size_t length) 
{
	if (munmap(addr, length) == -1) 
	{
		perror ("błąd usuwania odwzorowania pamieci dzielonej");
		exit (EXIT_FAILURE);
	}
}