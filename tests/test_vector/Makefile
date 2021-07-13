all:
	gcc -c test_vector.c -I../../include -o test_vector.o
	gcc -c ../../src/vector.c -I../../include -o vector.o
	gcc -c ../../src/standard.c -I../../include -o standard.o
	gcc test_vector.o vector.o standard.o -o main.out
	./main.out

clean:
	rm -rf *.o *.out