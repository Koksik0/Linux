DIR = $(notdir $(CURDIR))

Name1 = powielacz
Name2 = wzajemneWykluczanie
Lib = semafory
iloscProcesow = 5
iloscSekcji = 6
Plik = numer.txt
Semafor = Pawel

Exec1  = $(Name1).x
Exec2  = $(Name2).x

Objs1  = $(Name1).o
Objs2  = $(Name2).o

Libs  = $(Lib).c

CFLAGS = -pthread -Wall -std=c99 -pedantic -O
LFLAGS = -pthread -Wall -std=c99 -pedantic -O

CO = gcc
LD = $(CO)

%.o: %.c
	$(CO) $(CFLAGS) -c $<

$(Exec1): $(Objs1) $(Libs) 
	$(LD) -o $@ $(LFLAGS) $^

$(Exec2): $(Objs2) $(Libs) 
	$(LD) -o $@ $(LFLAGS) $^

run: $(Exec1) $(Exec2)
	./$(Exec1) $(Exec2) $(iloscProcesow) $(iloscSekcji) $(Plik) $(Semafor)

clean:
	rm -f *.o *~ *.x; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )