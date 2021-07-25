%{
#define SWIG_FILE_WITH_INIT
#include <assert.h>
#include "init.h"
#include "standard.h"
#include "vector.h"
#include "matrix.h"
#include "plot.h"
#ifndef __ADDITIONAL_FEATURE_H
#define __ADDITIONAL_FEATURE_H
static int isErr = 0;
struct s_iter {
    double *ptr;
    int len;
};
#endif
%}

#ifndef __S_ITER_H
#define __S_ITER_H
%exception s_iter::__next__ {
    assert(!isErr);
    $action
    if (isErr) {
        isErr = 0;
        PyErr_SetString(PyExc_StopIteration, "End of Iterator");
        return NULL;
    }
}

struct s_iter {
    double *ptr;
    int len;
};

%extend s_iter {
    struct s_iter *__iter__()
    {
        return $self;
    }

    double __next__() {
        if ($self->len--) {
            return *$self->ptr++;
        }
        isErr = 1;
        return 0;
    }
};
#endif

#ifndef __INCLUDE_NUMPY_I
#define __INCLUDE_NUMPY_I
%include "numpy.i"

%init %{
import_array();
%}
#endif