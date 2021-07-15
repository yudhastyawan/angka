all:
	make compile --directory=../../
	make test

test:
	gcc -c main_1.c -I../../include -o main.o
	gcc main.o -L../../lib/ -langka -o ./main.out
	./main.out
	rm -rf *.o *.out

clean:
	rm -f ../../lib/libangka.a