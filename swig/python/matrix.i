%include base.i

%typemap(in) (int pyrow, int pycol) {
    if (!PyTuple_Check($input)) return NULL;
    for (int i = 0; i < 2; i++) {
        PyObject *o = PyTuple_GetItem($input, i);
        if (PyNumber_Check(o)) {
            if (i == 0) {
                $1 = PyLong_AsLong(o);
            } else {
                $2 = PyLong_AsLong(o);
            }
        } else {
            Py_DECREF(o);
            return NULL;
        }
        Py_DECREF(o);
    }
}

%apply int *OUTPUT {int *rowout, int *colout};
%typemap(argout) (int *rowout, int *colout) {
    $result = PyTuple_New(2);
    PyTuple_SetItem($result, 0, PyLong_FromLong(*$1));
    PyTuple_SetItem($result, 1, PyLong_FromLong(*$2));
}

%apply (double *IN_ARRAY1, int DIM1) {(double *ndarray_in, int size)};
%apply (double **ARGOUTVIEW_ARRAY1, int *DIM1) {(double **ndarray_out, int *size)};
%apply (double *IN_ARRAY2, int DIM1, int DIM2) {(double *ndarray_in, int dim1, int dim2)};
%apply (double **ARGOUTVIEW_ARRAY2, int *DIM1, int *DIM2) {(double **ndarray_out, int *dim1, int *dim2)};

%include "matrix.h"

%extend s_matrix {
    s_matrix(int dim) {
        AgxMatrix *mat = agx_matrix_new_zero(dim, dim);
        return mat;
    }

    s_matrix(int row, int col) {
        AgxMatrix *mat = agx_matrix_new_zero(row, col);
        return mat;
    }

    s_matrix(int row, int col, double val) {
        AgxMatrix *mat = agx_matrix_new_constant(row, col, val);
        return mat;
    }

    s_matrix(double *ndarray_in, int dim1, int dim2) {
        AgxMatrix *mat = agx_matrix_new_from_array(ndarray_in, dim1, dim2);
        return mat;
    }

    s_matrix(AgxMatrix *mat_in) {
        AgxMatrix *mat = agx_matrix_new_duplicate_size(mat_in);
        agx_matrix_change_elements_by_value(mat, 0.);
        return mat;
    }

    s_matrix(AgxVector *vec) {
        AgxMatrix *mat = agx_matrix_new_from_vector(vec);
        return mat;
    }

    s_matrix(double *ndarray_in, int size) {
        AgxVector *vec = agx_vector_new_from_array(ndarray_in, size);
        AgxMatrix *mat = agx_matrix_new_from_vector(vec);
        agx_vector_delete(vec);
        return mat;
    }

    ~s_matrix() {
        agx_matrix_delete($self);
    }

    void constant(double val) {
        agx_matrix_change_elements_by_value($self, val);
    }

    void random(double min, double max) {
        AgxMatrix *mat_new = agx_matrix_new_random($self->r_shape[0], $self->r_shape[1], min, max);
        agx_matrix_copy_elements(mat_new, $self);
        agx_matrix_delete(mat_new);
    }

    struct s_iter __iter__() {
        struct s_iter ret;
        ret.ptr = $self->p_r_nums;
        ret.len = $self->size;
        return ret;
    }

    double __getitem__(int pyrow, int pycol) {
        return agx_matrix_get_item($self, pyrow, pycol);
    }

    void __setitem__(int pyrow, int pycol, double value) {
        agx_matrix_set_item($self, pyrow, pycol, value);
    }

    p_matrixString_t __str__() {
        p_matrixString_t matrixString;
        matrixString = agx_matrix_to_string($self, 0);
        return matrixString;
    }

    void printFull() {
        agx_matrix_print_full($self);
    }

    void toNumpy(double **ndarray_out, int *dim1, int *dim2) {
        agx_matrix_to_array($self, ndarray_out, dim1, dim2);
    }

    AgxVector *toVector() {
        AgxVector *vec = agx_vector_new_from_matrix($self);
        return vec;
    }

    AgxMatrix *extractColumn(int col) {
        AgxMatrix *mat = agx_matrix_new_extract_column($self, col);
        return mat;
    }

    AgxMatrix *extractRow(int row) {
        AgxMatrix *mat = agx_matrix_new_extract_row($self, row);
        return mat;
    }

    AgxMatrix *extractRowCol(int row1, int row2, int col1, int col2) {
        AgxMatrix *mat = agx_matrix_new_extract_row_col($self, row1, row2, col1, col2);
    }

    double min() {
        return agx_matrix_min($self);
    }

    double max() {
        return agx_matrix_max($self);
    }

    int dims2index(int row, int col) {
        return agx_matrix_row_col_to_index($self, row, col);
    }

    int __len__() {
        return $self->size;
    }

    void getShape(int *rowout, int *colout) {
        *rowout = $self->r_shape[0];
        *colout = $self->r_shape[1];
    }

    AgxMatrix *__lshift__(double val) {
        AgxMatrix *res = agx_matrix_new_copy($self);
        agx_matrix_change_elements_by_value(res, val);
        return res;
    }

    AgxMatrix *__ilshift__(double val) {
        agx_matrix_change_elements_by_value($self, val);
        return $self;
    }

    AgxMatrix *__lshift__(AgxMatrix *mat_in) {
        AgxMatrix *res = agx_matrix_new_copy($self);
        agx_matrix_copy_elements(mat_in, res);
        return res;
    }

    AgxMatrix *__ilshift__(AgxMatrix *mat_in) {
        agx_matrix_copy_elements(mat_in, $self);
        return $self;
    }

    AgxMatrix *__add__(double val) {
        AgxMatrix *res = agx_matrix_new_copy($self);
        agx_matrix_add_by_value(res, val);
        return res;
    }

    AgxMatrix *__iadd__(double val) {
        agx_matrix_add_by_value($self, val);
        return $self;
    }

    AgxMatrix *__sub__(double val) {
        AgxMatrix *res = agx_matrix_new_copy($self);
        agx_matrix_substract_by_value(res, val);
        return res;
    }

    AgxMatrix *__isub__(double val) {
        agx_matrix_substract_by_value($self, val);
        return $self;
    }

    AgxMatrix *__mul__(double val) {
        AgxMatrix *res = agx_matrix_new_copy($self);
        agx_matrix_multiply_by_value(res, val);
        return res;
    }

    AgxMatrix *__imul__(double val) {
        agx_matrix_multiply_by_value($self, val);
        return $self;
    }

    AgxMatrix *__truediv__(double val) {
        AgxMatrix *res = agx_matrix_new_copy($self);
        agx_matrix_divide_by_value(res, val);
        return res;
    }

    AgxMatrix *__itruediv__(double val) {
        agx_matrix_divide_by_value($self, val);
        return $self;
    }

    AgxMatrix *copy() {
        AgxMatrix *res = agx_matrix_new_copy($self);
        return res;
    }

    AgxMatrix *__matmul__(AgxMatrix *mat2) {
        AgxMatrix *res = agx_matrix_new_multiplication($self, mat2);
        return res;
    }

    void copyShape(AgxMatrix *mat_in) {
        agx_matrix_copy_shape(mat_in, $self);
    }

    void transpose() {
        agx_matrix_transpose($self);
    }

%pythoncode %{
    @property
    def T(self):
        self.transpose()
        return self

    @property
    def shape(self):
        return self.getShape()
%}
};