compile:
	mkdir -p ./lib/
	gcc -c ./src/matrix.c -I./include -o ./lib/matrix.o
	gcc -c ./src/vector.c -I./include -o ./lib/vector.o
	gcc -c ./src/standard.c -I./include -o ./lib/standard.o
	gcc -c ./src/init.c -I./include -o ./lib/init.o
	ar rcs ./lib/libagx.a ./lib/matrix.o ./lib/vector.o ./lib/standard.o ./lib/init.o
	rm -rf ./lib/*.o

clean:
	rm -f ./lib/*.a