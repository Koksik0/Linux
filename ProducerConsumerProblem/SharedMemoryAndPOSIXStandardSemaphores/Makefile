DIR = $(notdir $(CURDIR))
SYSNAME = $(shell uname -s)

NAME1 = main
NAME2 = producent
NAME3 = konsument
NAME4 = semafory
NAME5 = pamiecDzielona
LIB1 = semafory
LIB2 = pamiecDzielona
nazwaSemaforProducent = semaforProducent
nazwaSemaforKonsument = semaforKonsument
nazwaPamieciDzielonej = pamiecDzielona
PLIK_WE = surowce
PLIK_WY = skonsumowane

EXEC1s = $(NAME1)s.x
EXEC2s = $(NAME2)s.x
EXEC3s = $(NAME3)s.x
EXEC1d1 = $(NAME1)d1.x
EXEC2d1 = $(NAME2)d1.x
EXEC3d1 = $(NAME3)d1.x
EXEC1d2 = $(NAME1)d2.x
EXEC2d2 = $(NAME2)d2.x
EXEC3d2 = $(NAME3)d2.x

OBJS1  = $(NAME1).o
OBJS2  = $(NAME2).o
OBJS3  = $(NAME3).o
OBJS4  = $(NAME4).o
OBJS5  = $(NAME5).o

LIB_NAME = Biblioteka
LIB_DIR = ./lib
LIB_STAT = lib$(LIB_NAME).a

ifeq ($(SYSNAME), Linux)
  LIB_SHAR = lib$(LIB_NAME).so
endif
ifeq ($(SYSNAME), Darwin)
  LIB_SHAR = lib$(LIB_NAME).dylib
endif
# Pliki skompilowane wchodzace do biblioteki
LIB_OBJS = $(OBJS4) $(OBJS5)
HEADS1 = $(NAME4).h
HEADS2 = $(NAME5).h

CFLAGS = -Wall -std=gnu99 -pedantic -O -pthread -fPIC
LFLAGS = -Wall -std=gnu99 -pedantic -O -pthread
LDLIBS = -lrt

CO = gcc
LD = $(CO)

AR = ar

ARFLAGS = rsv

%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<
%.o: %.c
	$(CO) $(CFLAGS) -c $<
# Tworzenie biblioteki statycznej
$(LIB_STAT): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $?
	mkdir -p $(LIB_DIR)
	mv $(LIB_STAT) $(LIB_DIR)
# Tworzenie biblioteki dzielonej 
$(LIB_SHAR): $(LIB_OBJS) 
ifeq ($(SYSNAME), Linux)
	$(LD) -shared -o $@ $(LFLAGS) $(LIB_OBJS)
endif
ifeq ($(SYSNAME), Darwin)
	$(LD) -dynamiclib -o $@ $(LFLAGS) $(LIB_OBJS) -install_name @rpath/$(LIB_DIR)/$@
endif
	mkdir -p $(LIB_DIR)
	mv $(LIB_SHAR) $(LIB_DIR)


$(EXEC1s): $(OBJS1) $(LIB_STAT) 
	rm -f $(LIB_DIR)/$(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EXEC2s): $(OBJS2) $(LIB_STAT) 
	rm -f $(LIB_DIR)/$(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EXEC3s): $(OBJS3) $(LIB_STAT)
	rm -f $(LIB_DIR)/$(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS3) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EXEC1d1): $(OBJS1) $(LIB_SHAR)
ifeq ($(SYSNAME), Linux)
	$(LD) -o $@ $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)
endif
ifeq ($(SYSNAME), Darwin)
	$(LD) -o $@ $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Xlinker -rpath -Xlinker $(CURDIR)
endif
$(EXEC2d1): $(OBJS2) $(LIB_SHAR)
ifeq ($(SYSNAME), Linux)
	$(LD) -o $@ $(LFLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)
endif
ifeq ($(SYSNAME), Darwin)
	$(LD) -o $@ $(LFLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Xlinker -rpath -Xlinker $(CURDIR)
endif
$(EXEC3d1): $(OBJS3) $(LIB_SHAR)
ifeq ($(SYSNAME), Linux)
	$(LD) -o $@ $(LFLAGS) $(OBJS3) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)
endif
ifeq ($(SYSNAME), Darwin)
	$(LD) -o $@ $(LFLAGS) $(OBJS3) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Xlinker -rpath -Xlinker $(CURDIR)
endif
$(EXEC1d2): $(OBJS1) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EXEC2d2): $(OBJS2) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EXEC3d2): $(OBJS3) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS3) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(OBJS1) $(OBJS2) $(OBJS3): $(HEADS1) $(HEADS2)

statycznie: $(EXEC1s) $(EXEC2s) $(EXEC3s)
	./$(EXEC1s) $(EXEC2s) $(EXEC3s)  $(PLIK_WE) $(PLIK_WY) $(nazwaSemaforProducent) $(nazwaSemaforKonsument) $(nazwaPamieciDzielonej)
	diff -s $(PLIK_WE) $(PLIK_WY)

dynamicznie1: $(EXEC1d1) $(EXEC2d1) $(EXEC3d1)
	./$(EXEC1d1) $(EXEC2d1) $(EXEC3d1) $(PLIK_WE) $(PLIK_WY) $(nazwaSemaforProducent) $(nazwaSemaforKonsument) $(nazwaPamieciDzielonej)
	diff -s $(PLIK_WE) $(PLIK_WY)

dynamicznie2: $(EXEC1d2) $(EXEC2d2) $(EXEC3d2)
ifeq ($(SYSNAME), Linux)
	( export LD_LIBRARY_PATH=${LIB_DIR}:${LD_LIBRARY_PATH}; \
	./$(EXEC1d2) $(EXEC2d2) $(EXEC3d2) $(PLIK_WE) $(PLIK_WY) $(nazwaSemaforProducent) $(nazwaSemaforKonsument) $(nazwaPamieciDzielonej))
	diff -s $(PLIK_WE) $(PLIK_WY)
endif
ifeq ($(SYSNAME), Darwin)
	export DYLD_LIBRARY_PATH=${LIB_DIR}:${LD_LIBRARY_PATH}; \
	./$(EXEC1d2) $(EXEC2d2) $(EXEC3d2) $(PLIK_WE) $(PLIK_WY) $(nazwaSemaforProducent) $(nazwaSemaforKonsument) $(nazwaPamieciDzielonej))
	diff -s $(PLIK_WE) $(PLIK_WY)
endif

clean:
	rm -f *.o  *~ *.a *.so *.x ; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR))