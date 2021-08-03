GTKLIBS=`pkg-config --libs gtk+-3.0`
LIBLOC=../../lib
INCLOC=../../include

all:
	make test_1
	make test_2
	make test_3
	make test_4
	make test_5

test_1:
	gcc -c main_1.c -I$(INCLOC) -o main.o
	gcc main.o -L$(LIBLOC) -lagv -lagx $(GTKLIBS) -o ./main.out
	./main.out
	rm -rf *.o *.out

test_2:
	gcc -c main_2.c -I$(INCLOC) -o main.o
	gcc main.o -L$(LIBLOC) -lagv -lagx $(GTKLIBS) -o ./main.out
	./main.out
	rm -rf *.o *.out

test_3:
	gcc -c main_3.c -I$(INCLOC) -o main.o
	gcc main.o -L$(LIBLOC) -lagv -lagx $(GTKLIBS) -o ./main.out
	./main.out
	rm -rf *.o *.out

test_4:
	gcc -c main_4.c -I$(INCLOC) -o main.o
	gcc main.o -L$(LIBLOC) -lagv -lagx $(GTKLIBS) -o ./main.out
	./main.out
	rm -rf *.o *.out

test_5:
	gcc -c main_5.c -I$(INCLOC) -o main.o
	gcc main.o -L$(LIBLOC) -lagv -lagx $(GTKLIBS) -o ./main.out
	./main.out
	rm -rf *.o *.out

test_6:
	gcc -c main_6.c -I$(INCLOC) -o main.o
	gcc main.o -L$(LIBLOC) -lagv -lagx $(GTKLIBS) -o ./main.out
	./main.out
	rm -rf *.o *.out

.PHONY: all test_1 test_2 test_3 test_4 test_5 test_6