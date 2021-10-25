PYROOT=pyversions/
PYLOC=/usr/bin/
GTKLIBS=`pkg-config --libs gtk+-3.0`
LIBLOC=../../lib
INCLOC=../../include
INCNUMLOC=C:/ProgramData/Miniconda3/Lib/site-packages/numpy/core/include
INCNUMLIB=C:/ProgramData/Miniconda3/Lib/site-packages/numpy/core/lib
FLAGS=-O2 -fPIC

all:
	rm -rf dist/*
	for ver in 37 38 39; do \
	swig -python -I${INCLOC} -I${INCNUMLOC} angka.i; \
	gcc $(FLAGS) -c angka_wrap.c -I${INCLOC} -I${PYROOT}python$${ver}/include -I${INCNUMLOC} -o ${LIBLOC}/angka_wrap.o; \
	gcc -shared ${LIBLOC}/*.o -L${PYROOT}python$${ver}/libs -L${INCNUMLIB} -L${LIBLOC} -lpython$${ver} -lnpymath -lagv -lagx $(GTKLIBS) -lm -o py$${ver}/src/angka/_angka.pyd; \
	mv angka.py py$${ver}/src/angka/api.py; \
	mkdir -p py$${ver}/src/angka/libs; \
	mkdir -p py$${ver}/src/angka/include; \
	cp -r $(LIBLOC)/*.a py$${ver}/src/angka/libs; \
	cp -r $(INCLOC)/*.h py$${ver}/src/angka/include; \
	rm -rf ${LIBLOC}/*.o *.py *_wrap.c; \
	cd py$${ver}/; ${PYLOC}python -m build; rm -rf src/*.egg-info/; \
	cd ..; \
	mkdir -p dist/; \
	cp -r py$${ver}/dist/* dist/; \
	rm -rf py$${ver}/dist; \
	rm -rf py$${ver}/src/angka/include; \
	rm -rf py$${ver}/src/angka/libs; \
	done
	rm -rf dist/*.tar.gz

test:
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

upload:
	twine upload -r pypi dist/*

clean:
	rm -rf dist/*

.PHONY: all test upload clean