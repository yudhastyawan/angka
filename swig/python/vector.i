%include base.i

%typemap(in) (double *list, int size) {
    if (!PyList_Check($input)) return NULL;
    $2 = PyList_Size($input);
    $1 = (double *) malloc(($2)*sizeof(double));
    for (int i = 0; i < $2; i++) {
        PyObject *o = PyList_GetItem($input, i);
        if (PyNumber_Check(o)) {
            $1[i] = PyFloat_AsDouble(o);
        } else {
            Py_DECREF(o);
            return NULL;
        }
        Py_DECREF(o);
    }
}

%apply (double *IN_ARRAY1, int DIM1) {(double *ndarray_in, int size)};
%apply (double **ARGOUTVIEW_ARRAY1, int *DIM1) {(double **ndarray_out, int *size)};

%include "vector.h"

%extend s_vector {
    s_vector(int size) {
        AgxVector *vec = agx_vector_new_zero(size);
        return vec;
    }

    s_vector(int size, double val) {
        AgxVector *vec = agx_vector_new_constant(size, val);
        return vec;
    }

    s_vector(double *ndarray_in, int size) {
        AgxVector *vec = agx_vector_new_from_array(ndarray_in, size);
        return vec;
    }

    s_vector(double *list, int size) {
        AgxVector *vec = agx_vector_new_from_array(list, size);
        return vec;
    }

    ~s_vector() {
        agx_vector_delete(&$self);
    }

    struct s_iter __iter__() {
        struct s_iter ret;
        ret.ptr = $self->p_r_nums;
        ret.len = $self->size;
        return ret;
    }

    double __getitem__(int index) {
        double output;
        agx_vector_get_item($self, index, &output);
        return output;
    }

    void __setitem__(int index, double value) {
        agx_vector_set_item($self, index, value);
    }

    void constant(double val) {
        agx_vector_change_elements_by_value($self, val);
    }

    void random(double min, double max) {
        AgxVector *vec_new = agx_vector_new_random($self->size, min, max);
        agx_vector_copy_elements(vec_new, $self);
        agx_vector_delete(&vec_new);
    }

    void linspace(double min, double max) {
        AgxVector *vec_new = agx_vector_new_linspace(min, max, $self->size);;
        agx_vector_copy_elements(vec_new, $self);
        agx_vector_delete(&vec_new);
    }

    p_vectorString_t __str__() {
        p_vectorString_t vectorString;
        vectorString = agx_vector_to_string($self, 0);
        return vectorString;
    }

    void printFull() {
        agx_vector_print_full($self);
    }

    void toNumpy(double **ndarray_out, int *size) {
        agx_vector_to_array($self, ndarray_out, size);
    }

    AgxMatrix *toMatrix() {
        AgxMatrix *mat = agx_matrix_new_from_vector($self);
        return mat;
    }

    double min() {
        return agx_vector_min($self);
    }

    double max() {
        return agx_vector_max($self);
    }

    int isexist(double val, int idx1, int idx2) {
        return agx_vector_isexist($self, idx1, idx2, val);
    }

    int __contains__(double val) {
        return agx_vector_isexist($self, 0, $self->size - 1, val);
    }

    int __len__() {
        return $self->size;
    }

    void sort() {
        agx_vector_sort($self);
    }

    void append(double val) {
        agx_vector_append_value($self, val);
    }

    void append(AgxVector *vec) {
        agx_vector_append_vector($self, vec);
    }

    void append(double *ndarray_in, int size) {
        AgxVector *vec_new = agx_vector_new_from_array(ndarray_in, size);
        agx_vector_append_vector($self, vec_new);
    }

    void append(double *list, int size) {
        AgxVector *vec_new = agx_vector_new_from_array(list, size);
        agx_vector_append_vector($self, vec_new);
    }

    AgxVector *__lshift__(double val) {
        AgxVector *res = agx_vector_new_copy($self);
        agx_vector_change_elements_by_value(res, val);
        return res;
    }

    AgxVector *__ilshift__(double val) {
        agx_vector_change_elements_by_value($self, val);
        return $self;
    }

    AgxVector *__add__(double val) {
        AgxVector *res = agx_vector_new_copy($self);
        agx_vector_add_by_value(res, val);
        return res;
    }

    AgxVector *__iadd__(double val) {
        agx_vector_add_by_value($self, val);
        return $self;
    }

    AgxVector *__sub__(double val) {
        AgxVector *res = agx_vector_new_copy($self);
        agx_vector_substract_by_value(res, val);
        return res;
    }

    AgxVector *__isub__(double val) {
        agx_vector_substract_by_value($self, val);
        return $self;
    }

    AgxVector *__mul__(double val) {
        AgxVector *res = agx_vector_new_copy($self);
        agx_vector_multiply_by_value(res, val);
        return res;
    }

    AgxVector *__imul__(double val) {
        agx_vector_multiply_by_value($self, val);
        return $self;
    }

    AgxVector *__truediv__(double val) {
        AgxVector *res = agx_vector_new_copy($self);
        agx_vector_divide_by_value(res, val);
        return res;
    }

    AgxVector *__itruediv__(double val) {
        agx_vector_divide_by_value($self, val);
        return $self;
    }

    AgxVector *copy() {
        AgxVector *res = agx_vector_new_copy($self);
        return res;
    }
};