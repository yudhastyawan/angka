all:
	make compile --directory=../../
	make test

test:
	gcc -c test_matrix_2.c -I../../include -o test_matrix.o
	gcc test_matrix.o -L../../lib/ -langka -o ./main.out
	./main.out
	rm -rf *.o *.out

clean:
	rm -f ../../lib/libangka.a