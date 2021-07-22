all:
	make angka --directory=../../
	make test

test:
	gcc -c show_a_matrix.c -I../../include -I../../visual/include -o main.o
	gcc main.o -L../../lib/ -lagv -lm `pkg-config --libs gtk+-3.0` -o ./main.out
	./main.out
	rm -rf *.o *.out

clean:
	make clean --directory=../../