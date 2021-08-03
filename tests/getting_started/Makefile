GTKLIBS=`pkg-config --libs gtk+-3.0`
LIBLOC=../../lib
INCLOC=../../include

all:
	make test_vec
	make test_mat
	make test_plot
	make test_imshow

test_vec:
	gcc -c create_a_vector.c -I$(INCLOC) -o main.o
	gcc main.o -L$(LIBLOC) -lagx -o ./main.out
	./main.out
	rm -rf *.o *.out

test_mat:
	gcc -c create_a_matrix.c -I$(INCLOC) -o main.o
	gcc main.o -L$(LIBLOC) -lagx -o ./main.out
	./main.out
	rm -rf *.o *.out

test_plot:
	gcc -c show_a_plot.c -I$(INCLOC) -o main.o
	gcc main.o -L$(LIBLOC) -lagv -lagx $(GTKLIBS) -o ./main.out
	./main.out
	rm -rf *.o *.out

test_imshow:
	gcc -c show_a_matrix.c -I$(INCLOC) -o main.o
	gcc main.o -L$(LIBLOC) -lagv -lagx $(GTKLIBS) -o ./main.out
	./main.out
	rm -rf *.o *.out

.PHONY: all test_vec test_mat test_plot test_imshow