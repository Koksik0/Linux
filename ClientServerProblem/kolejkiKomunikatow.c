#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include "kolejkiKomunikatow.h"

mqd_t stworzKolejkeKomunikatow(const char *name, int oflag, int czyWyswietlacAtrybuty) 
{
	struct mq_attr attr;
	attr.mq_maxmsg = maxymalnaIloscWiadomosci;
	attr.mq_msgsize = maxymalnaDlugosckomunikatu;
	mqd_t deskryptorStworzeniaKolejkiKomunikatow = mq_open(name, O_CREAT | O_EXCL | oflag, 0644, &attr);
	if(deskryptorStworzeniaKolejkiKomunikatow == -1) 
	{
		perror("błąd tworzenia kolejki");
		exit(EXIT_FAILURE);
	}
	if(czyWyswietlacAtrybuty)
	{
		printf("Utworzono kolejkę \"%s\" deskryptor %d\n", nazwaKolejkiKomunikatow, deskryptorStworzeniaKolejkiKomunikatow);
		wypiszAtrybutyKolejkiKomunikatow(deskryptorStworzeniaKolejkiKomunikatow);
	}
	return deskryptorStworzeniaKolejkiKomunikatow;
}

mqd_t otworzKolejkeKomunikatow(const char *name, int oflag, int czyWyswietlacAtrybuty) 
{
	mqd_t deskryptorOtwarciaKolejkiKomunikatow = mq_open(name, oflag);
	if(deskryptorOtwarciaKolejkiKomunikatow == -1) 
	{
		perror("błąd otwierania kolejki");
		exit(EXIT_FAILURE);
	}
	if(czyWyswietlacAtrybuty)
	{
		printf("Otworzono kolejkę \"%s\" o deskryptorze %d\n", nazwaKolejkiKomunikatow, deskryptorOtwarciaKolejkiKomunikatow);
		wypiszAtrybutyKolejkiKomunikatow(deskryptorOtwarciaKolejkiKomunikatow);
	}
	return deskryptorOtwarciaKolejkiKomunikatow;
}

void wyjslijDoKolejkiKomunikatow(mqd_t mq_des, const char *msg_ptr,unsigned int msg_prio) 
{
	if(mq_send(mq_des, msg_ptr, maxymalnaDlugosckomunikatu, msg_prio) == -1) 
	{
		perror("Błąd wysyłania komunikatu");
		exit(EXIT_FAILURE);
	}
}

void odbierzZKolejkikomunikatow(mqd_t mq_des, char *msg_ptr,unsigned int *msg_prio) 
{
	if(mq_receive(mq_des, msg_ptr, maxymalnaDlugosckomunikatu, msg_prio) == -1) 
	{
		perror("Błąd odbierania komunikatu");
		exit(EXIT_FAILURE);
	}
}

void zamknijKolejkeKomunikatow(mqd_t mq_des) 
{
	if(mq_close(mq_des) == -1) 
	{
		perror("Błąd zamykania kolejki");
		exit(EXIT_FAILURE);
	}
}

void usunKolejkeKomunikatow(const char *name) 
{
	if(mq_unlink(name) == -1) 
	{
		perror("Błąd usuwania kolejki");
		exit(EXIT_FAILURE);
	}
}
void wypiszAtrybutyKolejkiKomunikatow(mqd_t mq_des)
{
	struct mq_attr attr;
	if(mq_getattr(mq_des, &attr) == -1) 
	{
		perror("Błąd pobierania atrybutów kolejki");
		exit(EXIT_FAILURE);
	}
	printf("Atrybuty kolejki: \n");
	printf("Flaga: = %ld\n", attr.mq_flags);
	printf("Maksymalna liczba komunikatow w kolejce: %ld\n", attr.mq_maxmsg);
	printf("Maksymalny rozmiar komunikatu (w bajtach): %ld\n", attr.mq_msgsize);
	printf("Liczba komunikatow aktualnie w kolejce: %ld\n\n", attr.mq_curmsgs);
}