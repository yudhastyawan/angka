compile:
	mkdir -p ./../lib/
	gcc -c ./src/plot.c -I./include -I./../include `pkg-config --cflags gtk+-3.0` -o ./../lib/plot.o
	ar rcs ./../lib/libagv.a ./../lib/plot.o
	rm -rf ./../lib/*.o

clean:
	rm -f ./lib/libagv.a