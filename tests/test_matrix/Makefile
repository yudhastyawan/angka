LIBLOC=../../lib
INCLOC=../../include

all:
	make test_1
	make test_2

test_1:
	gcc -c main_1.c -I$(INCLOC) -o main.o
	gcc main.o -L$(LIBLOC) -lagx -o ./main.out
	./main.out
	rm -rf *.o *.out

test_2:
	gcc -c main_2.c -I$(INCLOC) -o main.o
	gcc main.o -L$(LIBLOC) -lagx -o ./main.out
	./main.out
	rm -rf *.o *.out

.PHONY: all test_1 test_2