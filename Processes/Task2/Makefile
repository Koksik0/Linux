#Plik makefile
DIR = $(notdir $(CURDIR))

Name1 = zadanie1
Name2 = zadanie2

Exec1 = $(Name1)
Objs1 = $(Name1).o

Exec2 = $(Name2)
Objs2 = $(Name2).o

Coflags = -Wall -std=c99 -pedantic -O
Ldflags = -Wall -std=c99 -pedantic -O
CO = gcc
LD = $(CO)

%.o: %.c
	$(CO) $(Coflags) -c $<

.Phony: $(Exec1)
$(Exec1): $(Objs1)
	$(LD) -o $@ $(Ldflags) $^
$(Exec2): $(Objs2)
	$(LD) -o $@ $(Ldflags) $^

run1: $(Exec1) $(Exec2)
	./$(Exec1) $(Exec2)
run2: $(Exec2)
	./$(Exec2)

clean:
	rm -f *.o *.x *.*~ *~;
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR))
