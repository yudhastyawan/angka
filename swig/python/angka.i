%module angka

%{
#define SWIG_FILE_WITH_INIT
#include "init.h"
#include "standard.h"
#include "vector.h"
#include "matrix.h"
#include "plot.h"
%}

%include "numpy.i"

%init %{
import_array();
%}

%apply (double *IN_ARRAY1, int DIM1) {(double *ndarray_in, int size)};
%apply (double **ARGOUTVIEW_ARRAY1, int *DIM1) {(double **ndarray_out, int *size)};
%apply (double *IN_ARRAY2, int DIM1, int DIM2) {(double *ndarray_in, int dim1, int dim2)};
%apply (double **ARGOUTVIEW_ARRAY2, int *DIM1, int *DIM2) {(double **ndarray_out, int *dim1, int *dim2)};

%include "init.h"
%include "standard.h"
%include "vector.h"
%include "matrix.h"
%include "plot.h"