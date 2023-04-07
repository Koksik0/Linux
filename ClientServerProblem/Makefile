DIR = $(notdir $(CURDIR))

Name1 = serwer
Name2 = klient
Lib = kolejki

Exec1  = $(Name1).x
Exec2  = $(Name2).x

Objs1  = $(Name1).o
Objs2  = $(Name2).o

Libs  = $(Lib).c

CFLAGS = -Wall -std=c99 -pedantic -O
LFLAGS = -Wall -std=c99 -pedantic -O
LDLIBS = -lrt

CO = gcc
LD = $(CO)

%.o: %.c
	$(CO) $(CFLAGS) -c $<

$(Exec1): $(Objs1) $(Libs) 
	$(LD) -o $@ $(LFLAGS) $^ $(LDLIBS)

$(Exec2): $(Objs2) $(Libs) 
	$(LD) -o $@ $(LFLAGS) $^ $(LDLIBS)

run: clean $(Exec1) $(Exec2)
	xterm -hold -title SERWER -bg navy -e ./$(Exec1) &
	xterm -hold -title KLIENT1 -bg darkgreen -e ./$(Exec2) &
	xterm -hold -title KLIENT2 -bg darkgreen -e ./$(Exec2) &
	xterm -hold -title KLIENT3 -bg darkgreen -e ./$(Exec2)

clean:
	rm -f *.o  *~ *.x; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )