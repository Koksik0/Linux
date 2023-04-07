#Plik makefile
DIR = $(notdir $(CURDIR))

Plik1 = plik1.txt
Plik2 = plik2.txt

Name1 = zadanie1

Exec1 = $(Name1)
Objs1 = $(Name1).o

Coflags = -Wall -std=c99 -pedantic -O
Ldflags = -Wall -std=c99 -pedantic -O
CO = gcc
LD = $(CO)

%.o: %.c
	$(CO) $(Coflags) -c $<

.Phony: $(Exec1)
$(Exec1): $(Objs1)
	$(LD) -o $@ $(Ldflags) $^

run1: $(Exec1)
	./$(Exec1) $(Plik1) $(Plik2)
	diff -s $(Plik1) $(Plik2)

clean:
	rm -f *.o *.x *.*~ *~;
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR))
