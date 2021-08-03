%define ANGKADOC
"Python module from C Angka library"
%enddef
%module(docstring=ANGKADOC) angka
%feature("autodoc", "3");

%include base.i
%include "init.h"
%include "standard.h"
%include vector.i
%include matrix.i
%include visual.i