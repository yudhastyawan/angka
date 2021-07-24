all:
	make angka
	make visual

angka:
	mkdir -p ./lib/
	gcc -c ./src/matrix.c -I./include -o ./lib/matrix.o
	gcc -c ./src/vector.c -I./include -o ./lib/vector.o
	gcc -c ./src/standard.c -I./include -o ./lib/standard.o
	gcc -c ./src/init.c -I./include -o ./lib/init.o
	ar rcs ./lib/libagx.a ./lib/init.o ./lib/standard.o ./lib/vector.o ./lib/matrix.o
	rm -rf ./lib/*.o

visual:
	mkdir -p ./lib/
	gcc -c ./src/matrix.c -I./include -o ./lib/matrix.o
	gcc -c ./src/vector.c -I./include -o ./lib/vector.o
	gcc -c ./src/standard.c -I./include -o ./lib/standard.o
	gcc -c ./src/init.c -I./include -o ./lib/init.o
	gcc -c ./visual/src/plot.c -I./visual/include -I./include `pkg-config --cflags gtk+-3.0` -o ./lib/plot.o
	ar rcs ./lib/libagv.a ./lib/plot.o ./lib/init.o ./lib/standard.o ./lib/vector.o ./lib/matrix.o
	rm -rf ./lib/*.o

clean:
	rm -f ./lib/*.a

.PHONY: all angka visual clean