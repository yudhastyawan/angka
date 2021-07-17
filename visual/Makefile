compile:
	mkdir -p ./../lib/
	gcc -c ./../src/init.c -I./../include -o ./../lib/init.o
	gcc -c ./src/plot.c -I./include -I./../include `pkg-config --cflags gtk+-3.0` -o ./../lib/plot.o
	ar rcs ./../lib/libagv.a ./../lib/plot.o ./../lib/init.o
	rm -rf ./../lib/*.o

clean:
	rm -f ./lib/libagv.a