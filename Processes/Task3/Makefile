#Plik makefile
DIR = $(notdir $(CURDIR))

NrMetody = 2
NrSygnalu = 2

Name1 = zadanie1
Name2 = zadanie2
Name3 = zadanie3
Name4 = zadanie4

Exec1 = $(Name1)
Objs1 = $(Name1).o

Exec2 = $(Name2)
Objs2 = $(Name2).o

Exec3 = $(Name3)
Objs3 = $(Name3).o

Exec4 = $(Name4)
Objs4 = $(Name4).o

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
$(Exec3): $(Objs3)
	$(LD) -o $@ $(Ldflags) $^
$(Exec4): $(Objs4)
	$(LD) -o $@ $(Ldflags) $^

run1: $(Exec1)
	./$(Exec1) $(NrMetody) $(NrSygnalu)
run2: $(Exec2) $(Exec1)
	./$(Exec2) $(Exec1) $(NrMetody) $(NrSygnalu)
run3: $(Exec3) $(Exec4) $(Exec1)
	./$(Exec3) $(Exec4) $(Exec1) $(NrMetody) $(NrSygnalu)


clean:
	rm -f *.o *.x *.*~ *~;
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR))
