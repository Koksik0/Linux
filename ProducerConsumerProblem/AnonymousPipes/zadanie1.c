#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
int main(int narg, char *argv[])
{
    if(narg!=3)
    {
        perror("Powinny być przekazane dwa argumenty!!!");
        exit(1);
    }
    const int MAX_COUNT = 20;
    int stat_lock;
    char buf[MAX_COUNT];
    int fd[2];
    int plik,odczyt;
    char wypisz[13+MAX_COUNT];
    char wypisz1[20+MAX_COUNT];
    if(pipe(fd)==-1)
    {
        perror("Błąd pipe()");
    }
    switch(fork())
    {
        case -1:
        perror("Błąd fork");
        case 0:
            if (close (fd[1]) == -1) 
            {
				perror ("Błąd zamknięcia potoku");
				exit (EXIT_FAILURE);
			}
			
			if ((plik = open (argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
				printf ("Błąd otwarcia pliku %s do zapisu", argv[2]);
				perror ("Błąd pliku");
				exit (EXIT_FAILURE);
			}
			while (1) 
            {
				sleep(3);
				odczyt = read(fd[0], &buf, MAX_COUNT);
				if (odczyt == -1) {
					printf("Błąd odczytu z potoku\n");
					exit(EXIT_FAILURE);
				} 
                else if (odczyt == 0) 
                {
					break;
				} 
                else 
                {
					if(write (plik, &buf, odczyt)==-1)
                    {
                        perror("Błąd");
                        exit(0);
                    }
					buf[odczyt] = '\0';
					// (komunikat, "%s%s%s", "Konsumuje <= ", buf, "\n");
                    strcpy(wypisz,"Odebrane: ");
                    strcat(wypisz,buf);
                    strcat(wypisz,"\n");
                    if(write(1,wypisz,sizeof(wypisz))==-1)
                    {
                        perror("Błąd");
                        exit(0);
                    }
				}
			}
			if (close (plik) == -1) {
				perror ("Błąd zamknięcia pliku wyjścia");
				exit (EXIT_FAILURE);
			}
			if (close (fd[0]) == -1) {
				perror ("Błąd zamknięcia potoku");
				exit (EXIT_FAILURE);
			}
			break;
        default:
            if(close(fd[0]==-1))
            {
                perror("Błąd");
                exit(0);
            }
            if ((plik = open (argv[1], O_RDONLY, 0644)) == -1) {
				printf ("Błąd otwarcia pliku %s do odczytu", argv[1]);
				perror ("Błąd pliku");
				exit (EXIT_FAILURE);
			}
            while (1) 
            {
				sleep(3);
				odczyt = read(plik, &buf, MAX_COUNT);
				if (odczyt == -1) {
					printf("Błąd odczytu z pliku\n");
					exit(EXIT_FAILURE);
				} else if (odczyt == 0) {
					break;
				} 
                else 
                {
					if(write (fd[1], &buf, odczyt)==-1)
                    {
                        perror("Błąd");
                        exit(0);
                    }
					buf[odczyt] = '\0';
                    strcpy(wypisz1,"Produkuje: ");
                    strcat(wypisz1,buf);
                    strcat(wypisz1,"\n");
                    if(write(1,wypisz1,sizeof(wypisz1))==-1)
                    {
                        perror("Błąd");
                        exit(0);
                    }
				}
			}
			if (close (plik) == -1) {
				perror ("Błąd zamknięcia pliku wyjścia");
				exit (EXIT_FAILURE);
			}
			if (close (fd[1]) == -1) {
				perror ("Błąd zamknięcia potoku");
				exit (EXIT_FAILURE);
			}
			if (wait (&stat_lock) == -1) {
				perror ("Błąd wait");
				exit (EXIT_FAILURE);
			}
			break;
    }
}

