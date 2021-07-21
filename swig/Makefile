compile:
	mkdir -p ./../lib/
	gcc -O2 -fPIC -c ./../src/matrix.c -I./../include -o ./../lib/matrix.o
	gcc -O2 -fPIC -c ./../src/vector.c -I./../include -o ./../lib/vector.o
	gcc -O2 -fPIC -c ./../src/standard.c -I./../include -o ./../lib/standard.o
	gcc -O2 -fPIC -c ./../src/init.c -I./../include -o ./../lib/init.o
	gcc -O2 -fPIC -c ./../visual/src/plot.c -I./../include -I./../visual/include `pkg-config --cflags gtk+-3.0` -o ./../lib/plot.o
	swig -python -I./../include -I./../visual/include angka.i
	gcc -O2 -fPIC -c angka_wrap.c -I./../include -I./../visual/include -IC:/Users/Lenovo/.conda/envs/python37/include -o ./../lib/angka_wrap.o
	gcc -shared ./../lib/*.o -LC:/Users/Lenovo/.conda/envs/python37/libs -lpython37 `pkg-config --libs gtk+-3.0` -lm -o _angka.pyd
	rm -rf ./../lib/*.o

clean:
	rm -rf *.pyd *_wrap.c *.py