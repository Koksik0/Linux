#include <fcntl.h>
#include <sys/stat.h> 
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

sem_t *stworzSemafor(const char *,int);
sem_t *otworzSemafor(const char *);
void zamknijSemafor(sem_t *);
void wartoscSemafor(sem_t *,int *);
void podniesSemafor(sem_t *);
void opuscSemafor(sem_t *);
void usunSemafor(const char *);