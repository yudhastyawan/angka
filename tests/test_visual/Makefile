all:
	make compile --directory=../../
	make compile --directory=../../visual/
	make test

test:
	gcc -c main_3.c -I../../include -I../../visual/include -o main.o
	gcc main.o -L../../lib -lagx -lagv `pkg-config --libs gtk+-3.0` -lm -o ./main.out
	./main.out
	rm -rf *.o *.out

clean:
	rm -f ../../lib/*.a