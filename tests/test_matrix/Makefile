all:
	make compile
	make test
	make clean

test:
	gcc -c test_matrix_2.c -I../../include -o test_matrix.o
	gcc test_matrix.o -L../../lib/ -langka -o ./main.out
	./main.out
	rm -rf *.o *.out

compile:
	gcc -c ../../src/matrix.c -I../../include -o matrix.o
	gcc -c ../../src/vector.c -I../../include -o vector.o
	gcc -c ../../src/standard.c -I../../include -o standard.o
	gcc -c ../../src/init.c -I../../include -o init.o
	ar rcs ../../lib/libangka.a matrix.o standard.o init.o vector.o
	rm -rf *.o

clean:
	rm -f ../../lib/libangka.a