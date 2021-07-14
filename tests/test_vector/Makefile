all:
	gcc -c test_vector_3.c -I../../include -o test_vector.o
	gcc -c ../../src/vector.c -I../../include -o vector.o
	gcc -c ../../src/standard.c -I../../include -o standard.o
	gcc -c ../../src/init.c -I../../include -o init.o
	gcc test_vector.o vector.o standard.o init.o -o main.out
	./main.out

clean:
	rm -rf *.o *.out