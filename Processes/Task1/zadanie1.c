#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
uid_t UID;
gid_t GID;
pid_t PID;
pid_t PPID;
pid_t PGID;

int main()
{
  UID = getuid();
  GID = getgid();
  PID = getpid();
  PPID = getppid();
  PGID = getpgid(getpid());
  printf("Id uzytkownika: %u\n",UID);
  printf("Id grupy: %u\n",GID);
  printf("Id procesu: %u\n",PID);
  printf("Id procesu macierzystego: %u\n",PPID);
  printf("Id grupy procesów: %u\n",PGID);
}
