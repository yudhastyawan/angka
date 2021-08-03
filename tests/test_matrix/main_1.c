#include "angka.h"

int main() {
    AgxMatrix *mat = agx_matrix_new_constant(4, 5, 2.);
    agx_matrix_print_partial(mat);

    agx_matrix_transpose(mat);
    agx_matrix_print_partial(mat); 

    agx_matrix_delete(&mat);
    return 0;
}