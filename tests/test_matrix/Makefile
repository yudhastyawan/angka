all:
	gcc -c test_matrix_1.c -I../../include -o test_matrix.o
	gcc -c ../../src/matrix.c -I../../include -o matrix.o
	gcc -c ../../src/standard.c -I../../include -o standard.o
	gcc test_matrix.o matrix.o standard.o -o main.out
	./main.out

clean:
	rm -rf *.o *.out