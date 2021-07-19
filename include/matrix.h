#ifndef __MATRIX_H
#define __MATRIX_H

#ifdef __cplusplus
extern "C" {
#endif

typedef char * p_matrixString_t;

typedef struct s_matrix {
    double *p_r_nums;
    int r_shape[2];
    int size;
} AgxMatrix;

AgxMatrix *agx_matrix_new(int row, int column);
void agx_matrix_delete(AgxMatrix *mat);
void *agx_matrix_change_elements_by_value(AgxMatrix *mat, double val);
AgxMatrix *agx_matrix_new_constant(int row, int column, double val);
AgxMatrix *agx_matrix_new_random(int row, int column, double min, double max);
int agx_matrix_row_col_to_index(AgxMatrix *mat, int row, int col);
void *agx_matrix_set_item(AgxMatrix *mat, int row, int col, double val);
double agx_matrix_get_item(AgxMatrix *mat, int row, int col);
p_matrixString_t agx_matrix_to_string(AgxMatrix *mat, int islong);
void *agx_matrix_print(AgxMatrix *mat, int islong);
void *agx_matrix_print_partial(AgxMatrix *mat);
void *agx_matrix_print_full(AgxMatrix *mat);
void *agx_matrix_add_by_value(AgxMatrix *mat, double val);
void *agx_matrix_substract_by_value(AgxMatrix *mat, double val);
void *agx_matrix_multiply_by_value(AgxMatrix *mat, double val);
void *agx_matrix_devide_by_value(AgxMatrix *mat, double val);
AgxMatrix *agx_matrix_new_duplicate_size(AgxMatrix *mat);
void *agx_matrix_copy_elements(AgxMatrix *src, AgxMatrix *target);
void *agx_matrix_copy_shape(AgxMatrix *src, AgxMatrix *target);
void *agx_matrix_transpose(AgxMatrix *mat);
AgxMatrix *agx_matrix_new_copy(AgxMatrix *mat);
AgxMatrix *agx_matrix_new_from_vector(AgxVector *vec);
AgxMatrix *agx_matrix_new_identity(int size);
AgxMatrix *agx_matrix_new_zero(int row, int col);
AgxMatrix *agx_matrix_new_multiplication(AgxMatrix *mat1, AgxMatrix *mat2);
AgxVector *agx_vector_new_from_matrix(AgxMatrix *mat);
AgxMatrix *agx_matrix_new_extract_column(AgxMatrix *mat, int col);
AgxMatrix *agx_matrix_new_extract_row(AgxMatrix *mat, int row);
AgxMatrix *agx_matrix_new_extract_row_col(AgxMatrix *mat, int row1, int row2, int col1, int col2);

#ifdef __cplusplus
}
#endif

#endif