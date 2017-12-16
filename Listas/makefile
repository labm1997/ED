IDIR=include
SDIR=src
TDIR=tests
ODIR=obj
CC=gcc
CFLAGS=-I $(IDIR)

_DEPS=listas.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=listas.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

_OBJTESTS=test.o
OBJTESTS=$(patsubst %,$(ODIR)/%,$(_OBJTESTS))

default: install

$(ODIR)/listas.o: $(SDIR)/listas.c $(DEPS)
	$(CC) -c $(SDIR)/listas.c -o $(ODIR)/listas.o $(CFLAGS)
	
$(ODIR)/test.o: $(TDIR)/test.c $(DEPS)
	$(CC) $(CFLAGS) -c $(TDIR)/test.c -o $(ODIR)/test.o 

install: $(OBJ)
	$(CC) -o main.bin $^ $(CFLAGS)
	
test: $(OBJ) $(OBJTESTS)
	$(CC) -o main.bin $^ $(CFLAGS) `pkg-config --cflags check` `pkg-config --libs check`

clean:
	rm -f $(ODIR)/*.o main.bin
