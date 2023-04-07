#Plik makefile
DIR = $(notdir $(CURDIR))

Name1 = zadanie1
Name2 = zadanie2
Name3 = zadanie3
Name4 = zadanie4
Name5 = zadanie5

Exec1 = $(Name1)
Objs1 = $(Name1).o

Exec2 = $(Name2)
Objs2 = $(Name2).o

Exec3 = $(Name3)
Objs3 = $(Name3).o

Exec4 = $(Name4)
Objs4 = $(Name4).o

Exec5 = $(Name5)
Objs5 = $(Name5).o

Coflags = -Wall -std=c99 -pedantic -O
Ldflags = -Wall -std=c99 -pedantic -O
CO = gcc
LD = $(CO)

%.o: %.c
	$(CO) $(Coflags) -c $<

.Phony: $(Exec1) $(Exec2) $(Exec3) $(Exec4) $(Exec5)
$(Exec1): $(Objs1)
	$(LD) -o $@ $(Ldflags) $^
$(Exec2): $(Objs2)
	$(LD) -o $@ $(Ldflags) $^
$(Exec3): $(Objs3)
	$(LD) -o $@ $(Ldflags) $^
$(Exec4): $(Objs4)
	$(LD) -o $@ $(Ldflags) $^
$(Exec5): $(Objs5)
	$(LD) -o $@ $(Ldflags) $^

run1: $(Exec1)
	./$(Exec1)
run2: $(Exec2)
	./$(Exec2)
run3: $(Exec3)
	./$(Exec3)
run4: $(Exec4)
	./$(Exec4)
run5: $(Exec5)
	./$(Exec5)
clean:
	rm -f *.o *.x *.*~ *~;
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR))
