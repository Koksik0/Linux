DIR = $(notdir $(CURDIR))

Plik1 = plik1.txt
Plik2 = plik2.txt
NazwaFIFO = mkfifo
Sciezka = ./

Name1 = main
Name2 = producer
Name3 = customer

Exec1 = $(Name1)
Objs1 = $(Name1).o

Exec2 = $(Name2)
Objs2 = $(Name2).o

Exec3 = $(Name3)
Objs3 = $(Name3).o

CFLAGS = -Wall -std=c99 -pedantic -O
LFLAGS = -Wall -std=c99 -pedantic -O

CO = gcc
LD = $(CO)

AR = ar

ARFLAGS = rsv

%.o: %.c
	$(CO) $(CFLAGS) -c $<

$(EXEC1): $(OBJS1) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^

$(EXECP): $(OBJSP) $(LIBSP) 
	$(LD) -o $@ $(LFLAGS) $^

$(EXECK): $(OBJSK) $(LIBSK) 
	$(LD) -o $@ $(LFLAGS) $^

run1: $(Exec1) $(Exec2) $(Exec3)
	./$(Exec1) $(Exec2) $(Exec3) $(Plik1) $(Plik2) $(NazwaFIFO)
	diff -s $(Plik1) $(Plik2)
run2: $(Exec2) $(Exec3)
	mkfifo -m 0644 $(NazwaFIFO)
	xterm -hold -title $(Name2) -e $(Sciezka)$(Exec2) $(Plik1) $(NazwaFIFO) & xterm -hold -title $(Name3) -e $(Sciezka)$(Exec3) $(Plik2) $(NazwaFIFO)
	rm $(NazwaFIFO)
	diff -s $(Plik1) $(Plik2)

clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )