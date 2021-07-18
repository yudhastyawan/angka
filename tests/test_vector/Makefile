all:
	make compile --directory=../../
	make test

test:
	gcc -c main_3.c -I../../include -o main.o
	gcc main.o -L../../lib/ -lagx -o ./main.out
	./main.out
	rm -rf *.o *.out

clean:
	rm -f ../../lib/libagx.a