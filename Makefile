GTKFLAGS=`pkg-config --cflags gtk+-3.0`
LIBLOC=./lib
INCLOC=./include
SRCLOC=./src/core
SRCVISLOC=./src/visual
FLAGS=-O2 -Wall -fPIC

all:
	make clean
	make angka
	make visual

angka:
	mkdir -p $(LIBLOC)/
	gcc $(FLAGS) -c $(SRCLOC)/matrix.c -I$(INCLOC) -o $(LIBLOC)/matrix.o
	gcc $(FLAGS) -c $(SRCLOC)/vector.c -I$(INCLOC) -o $(LIBLOC)/vector.o
	gcc $(FLAGS) -c $(SRCLOC)/standard.c -I$(INCLOC) -o $(LIBLOC)/standard.o
	gcc $(FLAGS) -c $(SRCLOC)/init.c -I$(INCLOC) -o $(LIBLOC)/init.o
	ar rcs $(LIBLOC)/libagx.a $(LIBLOC)/init.o $(LIBLOC)/standard.o $(LIBLOC)/vector.o $(LIBLOC)/matrix.o
	rm -rf $(LIBLOC)/*.o

visual:
	mkdir -p $(LIBLOC)/
	gcc $(FLAGS) -c $(SRCVISLOC)/visual.c -I$(INCLOC) $(GTKFLAGS) -o $(LIBLOC)/visual.o
	ar rcs $(LIBLOC)/libagv.a $(LIBLOC)/visual.o
	rm -rf $(LIBLOC)/*.o

clean:
	rm -rf $(LIBLOC)/*.a

.PHONY: all angka visual clean