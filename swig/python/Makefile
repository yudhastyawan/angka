ROOT=./../../
PYROOT=pyversions/
PYLOC=/usr/bin/
NUMLOC=C:/ProgramData/Miniconda3/Lib/site-packages/numpy/

all:
	rm -rf dist/*
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
	mkdir -p py37/src/angka/libs
	mkdir -p py37/src/angka/include
	ar rcs py37/src/angka/libs/libagx.a ${ROOT}lib/init.o ${ROOT}lib/standard.o ${ROOT}lib/vector.o ${ROOT}lib/matrix.o
	ar rcs py37/src/angka/libs/libagv.a ${ROOT}lib/plot.o ${ROOT}lib/init.o ${ROOT}lib/standard.o ${ROOT}lib/vector.o ${ROOT}lib/matrix.o
	cp -r ${ROOT}include/*.h py37/src/angka/include
	cp -r ${ROOT}visual/include/*.h py37/src/angka/include
	rm -rf ${ROOT}lib/*.o *.py *_wrap.c
	cd py37/; ${PYLOC}python -m build; rm -rf src/*.egg-info/
	mkdir -p dist/
	cp -r py37/dist/* dist/
	rm -rf py37/dist
	rm -rf py37/src/angka/include
	rm -rf py37/src/angka/libs

py37test:
	mkdir -p ${ROOT}lib/
	gcc -O2 -fPIC -c ${ROOT}src/matrix.c -I${ROOT}include -o ${ROOT}lib/matrix.o
	gcc -O2 -fPIC -c ${ROOT}src/vector.c -I${ROOT}include -o ${ROOT}lib/vector.o
	gcc -O2 -fPIC -c ${ROOT}src/standard.c -I${ROOT}include -o ${ROOT}lib/standard.o
	gcc -O2 -fPIC -c ${ROOT}src/init.c -I${ROOT}include -o ${ROOT}lib/init.o
	gcc -O2 -fPIC -c ${ROOT}visual/src/plot.c -I${ROOT}include -I${ROOT}visual/include `pkg-config --cflags gtk+-3.0` -o ${ROOT}lib/plot.o
	swig -python -I${ROOT}include -I${ROOT}visual/include -I${NUMLOC}core/include angka.i
	gcc -O2 -fPIC -c angka_wrap.c -I${ROOT}include -I${ROOT}visual/include -I${PYROOT}python37/include -I${NUMLOC}core/include -o ${ROOT}lib/angka_wrap.o
	gcc -shared ${ROOT}lib/*.o -L${PYROOT}python37/libs -L${NUMLOC}core/lib -lpython37 -lnpymath `pkg-config --libs gtk+-3.0` -lm -o tests/_angka.pyd
	mv angka.py tests/angka.py
	rm -rf ${ROOT}lib/*.o *.py *_wrap.c

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
	mkdir -p py38/src/angka/libs
	mkdir -p py38/src/angka/include
	ar rcs py38/src/angka/libs/libagx.a ${ROOT}lib/init.o ${ROOT}lib/standard.o ${ROOT}lib/vector.o ${ROOT}lib/matrix.o
	ar rcs py38/src/angka/libs/libagv.a ${ROOT}lib/plot.o ${ROOT}lib/init.o ${ROOT}lib/standard.o ${ROOT}lib/vector.o ${ROOT}lib/matrix.o
	cp -r ${ROOT}include/*.h py38/src/angka/include
	cp -r ${ROOT}visual/include/*.h py38/src/angka/include
	rm -rf ${ROOT}lib/*.o *.py *_wrap.c
	cd py38/; ${PYLOC}python -m build; rm -rf src/*.egg-info/
	mkdir -p dist/
	cp -r py38/dist/* dist/
	rm -rf py38/dist
	rm -rf py38/src/angka/include
	rm -rf py38/src/angka/libs

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
	mkdir -p py39/src/angka/libs
	mkdir -p py39/src/angka/include
	ar rcs py39/src/angka/libs/libagx.a ${ROOT}lib/init.o ${ROOT}lib/standard.o ${ROOT}lib/vector.o ${ROOT}lib/matrix.o
	ar rcs py39/src/angka/libs/libagv.a ${ROOT}lib/plot.o ${ROOT}lib/init.o ${ROOT}lib/standard.o ${ROOT}lib/vector.o ${ROOT}lib/matrix.o
	cp -r ${ROOT}include/*.h py39/src/angka/include
	cp -r ${ROOT}visual/include/*.h py39/src/angka/include
	rm -rf ${ROOT}lib/*.o *.py *_wrap.c
	cd py39/; ${PYLOC}python -m build; rm -rf src/*.egg-info/
	mkdir -p dist/
	cp -r py39/dist/* dist/
	rm -rf py39/dist
	rm -rf py39/src/angka/include
	rm -rf py39/src/angka/libs

upload:
	twine upload -r pypi dist/*

clean:
	rm -rf dist/*

.PHONY: all py37 py37test py38 py39 upload clean