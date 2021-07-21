#include "angka.h"

int main() {
    AgxMatrix *mat1 = agx_matrix_new_identity(5);
    AgxMatrix *mat2 = agx_matrix_new_random(5, 3, -10., 10.);
    
    agx_matrix_print_partial(mat1);
    agx_matrix_print_partial(mat2);

    AgxMatrix *res = agx_matrix_new_multiplication(mat1, mat2);

    agx_matrix_print_partial(res);
    AgxMatrix *mat3 = agx_matrix_new_extract_column(res, 1);
    // agx_matrix_print_partial(mat3);
    AgxVector *vec = agx_vector_new_from_matrix(res);
    // agx_vector_print_partial(vec);
    AgxMatrix *mat4 = agx_matrix_new_extract_row_col(res, 1, 4, 2, 2);
    agx_matrix_print_partial(mat4);

    agx_matrix_delete(mat1);
    agx_matrix_delete(mat2);
    agx_matrix_delete(res);
    agx_matrix_delete(mat3);
    agx_matrix_delete(mat4);
    agx_vector_delete(vec);
    return 0;
}