ROOT=./../../
PYROOT=pyversions/
PYLOC=/usr/bin/
NUMLOC=C:/ProgramData/Miniconda3/Lib/site-packages/numpy/

all:
	make py37
	make py38
	make py39
	rm -rf dist/*.tar.gz

py37:
	mkdir -p ${ROOT}lib/
	gcc -O2 -fPIC -c ${ROOT}src/matrix.c -I${ROOT}include -o ${ROOT}lib/matrix.o
	gcc -O2 -fPIC -c ${ROOT}src/vector.c -I${ROOT}include -o ${ROOT}lib/vector.o
	gcc -O2 -fPIC -c ${ROOT}src/standard.c -I${ROOT}include -o ${ROOT}lib/standard.o
	gcc -O2 -fPIC -c ${ROOT}src/init.c -I${ROOT}include -o ${ROOT}lib/init.o
	gcc -O2 -fPIC -c ${ROOT}visual/src/plot.c -I${ROOT}include -I${ROOT}visual/include `pkg-config --cflags gtk+-3.0` -o ${ROOT}lib/plot.o
	swig -python -I${ROOT}include -I${ROOT}visual/include -I${NUMLOC}core/include angka.i
	gcc -O2 -fPIC -c angka_wrap.c -I${ROOT}include -I${ROOT}visual/include -I${PYROOT}python37/include -I${NUMLOC}core/include -o ${ROOT}lib/angka_wrap.o
	gcc -shared ${ROOT}lib/*.o -L${PYROOT}python37/libs -L${NUMLOC}core/lib -lpython37 -lnpymath `pkg-config --libs gtk+-3.0` -lm -o py37/src/angka/_angka.pyd
	mv angka.py py37/src/angka/angka.py
	rm -rf ${ROOT}lib/*.o *.py *_wrap.c
	cd py37/; ${PYLOC}python -m build; rm -rf src/*.egg-info/
	mkdir -p dist/
	cp -r py37/dist/* dist/
	rm -rf py37/dist

py38:
	mkdir -p ${ROOT}lib/
	gcc -O2 -fPIC -c ${ROOT}src/matrix.c -I${ROOT}include -o ${ROOT}lib/matrix.o
	gcc -O2 -fPIC -c ${ROOT}src/vector.c -I${ROOT}include -o ${ROOT}lib/vector.o
	gcc -O2 -fPIC -c ${ROOT}src/standard.c -I${ROOT}include -o ${ROOT}lib/standard.o
	gcc -O2 -fPIC -c ${ROOT}src/init.c -I${ROOT}include -o ${ROOT}lib/init.o
	gcc -O2 -fPIC -c ${ROOT}visual/src/plot.c -I${ROOT}include -I${ROOT}visual/include `pkg-config --cflags gtk+-3.0` -o ${ROOT}lib/plot.o
	swig -python -I${ROOT}include -I${ROOT}visual/include -I${NUMLOC}core/include angka.i
	gcc -O2 -fPIC -c angka_wrap.c -I${ROOT}include -I${ROOT}visual/include -I${PYROOT}python38/include -I${NUMLOC}core/include -o ${ROOT}lib/angka_wrap.o
	gcc -shared ${ROOT}lib/*.o -L${PYROOT}python38/libs -L${NUMLOC}core/lib -lpython38 -lnpymath `pkg-config --libs gtk+-3.0` -lm -o py38/src/angka/_angka.pyd
	mv angka.py py38/src/angka/angka.py
	rm -rf ${ROOT}lib/*.o *.py *_wrap.c
	cd py38/; ${PYLOC}python -m build; rm -rf src/*.egg-info/
	mkdir -p dist/
	cp -r py38/dist/* dist/
	rm -rf py38/dist

py39:
	mkdir -p ${ROOT}lib/
	gcc -O2 -fPIC -c ${ROOT}src/matrix.c -I${ROOT}include -o ${ROOT}lib/matrix.o
	gcc -O2 -fPIC -c ${ROOT}src/vector.c -I${ROOT}include -o ${ROOT}lib/vector.o
	gcc -O2 -fPIC -c ${ROOT}src/standard.c -I${ROOT}include -o ${ROOT}lib/standard.o
	gcc -O2 -fPIC -c ${ROOT}src/init.c -I${ROOT}include -o ${ROOT}lib/init.o
	gcc -O2 -fPIC -c ${ROOT}visual/src/plot.c -I${ROOT}include -I${ROOT}visual/include `pkg-config --cflags gtk+-3.0` -o ${ROOT}lib/plot.o
	swig -python -I${ROOT}include -I${ROOT}visual/include -I${NUMLOC}core/include angka.i
	gcc -O2 -fPIC -c angka_wrap.c -I${ROOT}include -I${ROOT}visual/include -I${PYROOT}python39/include -I${NUMLOC}core/include -o ${ROOT}lib/angka_wrap.o
	gcc -shared ${ROOT}lib/*.o -L${PYROOT}python39/libs -L${NUMLOC}core/lib -lpython39 -lnpymath `pkg-config --libs gtk+-3.0` -lm -o py39/src/angka/_angka.pyd
	mv angka.py py39/src/angka/angka.py
	rm -rf ${ROOT}lib/*.o *.py *_wrap.c
	cd py39/; ${PYLOC}python -m build; rm -rf src/*.egg-info/
	mkdir -p dist/
	cp -r py39/dist/* dist/
	rm -rf py39/dist

upload:
	twine upload -r pypi dist/*

clean:
	rm -rf dist/*

.PHONY: all py37 py38 py39 upload clean