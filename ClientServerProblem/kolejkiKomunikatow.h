#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <mqueue.h>
#ifndef KOLEJKI_H
#define KOLEJKI_H

#define nazwaKolejkiKomunikatow "/PawelWaclawikaawegsa"
#define maxymalnaIloscWiadomosci 10
#define maxymalnaDlugosckomunikatu 30

mqd_t stworzKolejkeKomunikatow(const char *, int, int);
mqd_t otworzKolejkeKomunikatow(const char *, int, int);
void wyjslijDoKolejkiKomunikatow(mqd_t, const char *,unsigned int);
void odbierzZKolejkikomunikatow(mqd_t, char *,unsigned int *);
void zamknijKolejkeKomunikatow(mqd_t);
void usunKolejkeKomunikatow(const char *);
void wypiszAtrybutyKolejkiKomunikatow(mqd_t);

#endif