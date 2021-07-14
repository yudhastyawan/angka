all:
	make compile --directory=../../
	make test

test:
	gcc -c test_vector_3.c -I../../include -o test_vector.o
	gcc test_vector.o -L../../lib/ -langka -o ./main.out
	./main.out
	rm -rf *.o *.out

clean:
	rm -f ../../lib/libangka.a