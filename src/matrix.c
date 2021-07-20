#include "init.h"
#include "standard.h"
#include "vector.h"
#include "matrix.h"
#include <malloc.h>
#include <string.h>
#include <stdio.h>

AgxMatrix *agx_matrix_new(int row, int column) {
    AgxMatrix *mat;
    mat = (AgxMatrix *)malloc(sizeof(AgxMatrix));
    mat->size = row * column;
    mat->r_shape[0] = row;
    mat->r_shape[1] = column;
    mat->p_r_nums = (double *)malloc((mat->size)*sizeof(double));
    return mat;
}

void agx_matrix_delete(AgxMatrix *mat) {
    free(mat->p_r_nums);
    free(mat);
}

void *agx_matrix_change_elements_by_value(AgxMatrix *mat, double val) {
    for (int i = 0; i < mat->size; i++) {
        mat->p_r_nums[i] = val;
    }
}

AgxMatrix *agx_matrix_new_constant(int row, int column, double val) {
    AgxMatrix *mat = agx_matrix_new(row, column);
    agx_matrix_change_elements_by_value(mat, val);
    return mat;
}

AgxMatrix *agx_matrix_new_random(int row, int column, double min, double max) {
    AgxMatrix *mat = agx_matrix_new(row, column);
    double val;
    double *ptr;
    for (int i = 0; i < mat->size; i++) {
        val = agx_random(min, max);
        ptr = &val;
        mat->p_r_nums[i] = *ptr;
    }
    return mat;
}

int agx_matrix_row_col_to_index(AgxMatrix *mat, int row, int col) {
    return col + row*mat->r_shape[1];
}

void *agx_matrix_set_item(AgxMatrix *mat, int row, int col, double val) {
    int index = agx_matrix_row_col_to_index(mat, row, col);
    if (index < mat->size) {
        mat->p_r_nums[index] = val;
    } else {
        return NULL;
    }
}

double agx_matrix_get_item(AgxMatrix *mat, int row, int col) {
    return mat->p_r_nums[agx_matrix_row_col_to_index(mat, row, col)];
}

p_matrixString_t agx_matrix_to_string(AgxMatrix *mat, int islong) {
    char *mat_string;
    int mat_length;
    int i, j;

    // counting the string length
    mat_length += agx_string_length_string("shape (,)\n");
    mat_length += agx_string_length_integer(mat->r_shape[0]);
    mat_length += agx_string_length_integer(mat->r_shape[1]);
    if (islong == TRUE || (mat->r_shape[0] <= 5 && mat->r_shape[1] <= 5)) {
        // [],[],[]
        for (i = 0; i < mat->r_shape[0]; i++) {
            mat_length += agx_string_length_string("[]\n");
            for (j = 0; j < mat->r_shape[1]; j++) {
                mat_length += agx_string_length_double(mat->p_r_nums[agx_matrix_row_col_to_index(mat, i, j)]);
                if (j < mat->r_shape[1] - 1) {
                    mat_length += agx_string_length_string(", ");
                }
            }
        }
    } 
    else if (islong == FALSE && mat->r_shape[0] <= 5) {
        for (i = 0; i < mat->r_shape[0]; i++) {
            mat_length += agx_string_length_string("[]\n");
            for (j = 0; j < mat->r_shape[1]; j++) {
                if (j < 4) {
                    mat_length += agx_string_length_double(mat->p_r_nums[agx_matrix_row_col_to_index(mat, i, j)]);
                    if (j < 3) {
                        mat_length += agx_string_length_string(", ");
                    } else {
                        mat_length += agx_string_length_string(",..., ");
                    }
                }
                if (j == (mat->r_shape[1] - 1)) {
                    mat_length += agx_string_length_double(mat->p_r_nums[agx_matrix_row_col_to_index(mat, i, j)]);
                }
            }
        }
    }
    else if (islong == FALSE && mat->r_shape[1] <= 5) {
        for (i = 0; i < mat->r_shape[0]; i++) {
            if (i < 4 || i == (mat->r_shape[0]-1)) {
                mat_length += agx_string_length_string("[]\n");
                for (j = 0; j < mat->r_shape[1]; j++) {
                    mat_length += agx_string_length_double(mat->p_r_nums[agx_matrix_row_col_to_index(mat, i, j)]);
                    if (j < mat->r_shape[1] - 1) {
                        mat_length += agx_string_length_string(", ");
                    }
                }
                if (i == 3) {
                    mat_length += agx_string_length_string("\t...\n");
                }
            }
        }
    }
    else {
        for (i = 0; i < mat->r_shape[0]; i++) {
            if (i < 4 || i == (mat->r_shape[0]-1)) {
                mat_length += agx_string_length_string("[]\n");
                for (j = 0; j < mat->r_shape[1]; j++) {
                    if (j < 4) {
                        mat_length += agx_string_length_double(mat->p_r_nums[agx_matrix_row_col_to_index(mat, i, j)]);
                        if (j < 3) {
                            mat_length += agx_string_length_string(", ");
                        } else {
                            mat_length += agx_string_length_string(",..., ");
                        }
                    }
                    if (j == (mat->r_shape[1] - 1)) {
                        mat_length += agx_string_length_double(mat->p_r_nums[agx_matrix_row_col_to_index(mat, i, j)]);
                    }
                }
                if (i == 3) {
                    mat_length += agx_string_length_string("\t...\n");
                }
            }
        }
    }
    
    mat_length += 1;

    // designing the string
    mat_string = malloc(mat_length);
    strcpy(mat_string, "shape (");
    agx_string_append_integer(mat_string, mat->r_shape[0], FALSE);
    strcat(mat_string, ",");
    agx_string_append_integer(mat_string, mat->r_shape[1], FALSE);
    strcat(mat_string, ")\n");
    if (islong == TRUE || (mat->r_shape[0] <= 5 && mat->r_shape[1] <= 5)) {
        for (i = 0; i < mat->r_shape[0]; i++) {
            strcat(mat_string, "[");
            for (j = 0; j < mat->r_shape[1]; j++) {
                agx_string_append_double(mat_string, mat->p_r_nums[agx_matrix_row_col_to_index(mat, i, j)], FALSE);
                if (j < mat->r_shape[1] - 1) {
                    strcat(mat_string, ", ");
                }
            }
            strcat(mat_string, "]\n");
        }
    }
    else if (islong == FALSE && mat->r_shape[0] <= 5) {
        for (i = 0; i < mat->r_shape[0]; i++) {
            strcat(mat_string, "[");
            for (j = 0; j < mat->r_shape[1]; j++) {
                if (j < 4) {
                    agx_string_append_double(mat_string, mat->p_r_nums[agx_matrix_row_col_to_index(mat, i, j)], FALSE);
                    if (j < 3) {
                        strcat(mat_string, ", ");
                    } else {
                        strcat(mat_string, ",..., ");
                    }
                }
                if (j == (mat->r_shape[1] - 1)) {
                    agx_string_append_double(mat_string, mat->p_r_nums[agx_matrix_row_col_to_index(mat, i, j)], FALSE);
                }
            }
            strcat(mat_string, "]\n");
        }
    }
    else if (islong == FALSE && mat->r_shape[1] <= 5) {
        for (i = 0; i < mat->r_shape[0]; i++) {
            if (i < 4 || i == (mat->r_shape[0]-1)) {
                strcat(mat_string, "[");
                for (j = 0; j < mat->r_shape[1]; j++) {
                    agx_string_append_double(mat_string, mat->p_r_nums[agx_matrix_row_col_to_index(mat, i, j)], FALSE);
                    if (j < mat->r_shape[1] - 1) {
                        strcat(mat_string, ", ");
                    }
                }
                strcat(mat_string, "]\n");
                if (i == 3) {
                    strcat(mat_string, "\t...\n");
                }
            }
        }
    }
    else {
        for (i = 0; i < mat->r_shape[0]; i++) {
            if (i < 4 || i == (mat->r_shape[0]-1)) {
                strcat(mat_string, "[");
                for (j = 0; j < mat->r_shape[1]; j++) {
                    if (j < 4) {
                        agx_string_append_double(mat_string, mat->p_r_nums[agx_matrix_row_col_to_index(mat, i, j)], FALSE);
                        if (j < 3) {
                            strcat(mat_string, ", ");
                        } else {
                            strcat(mat_string, ",..., ");
                        }
                    }
                    if (j == (mat->r_shape[1] - 1)) {
                        agx_string_append_double(mat_string, mat->p_r_nums[agx_matrix_row_col_to_index(mat, i, j)], FALSE);
                    }
                }
                strcat(mat_string, "]\n");
                if (i == 3) {
                    strcat(mat_string, "\t...\n");
                }
            }
        }
    }

    return mat_string;
}

void *agx_matrix_print(AgxMatrix *mat, int islong) {
    p_matrixString_t mat_str = agx_matrix_to_string(mat, islong);
    printf("%s", mat_str);
    agx_data_delete(mat_str);
}

void *agx_matrix_print_partial(AgxMatrix *mat) {
    agx_matrix_print(mat, FALSE);
}

void *agx_matrix_print_full(AgxMatrix *mat) {
    agx_matrix_print(mat, TRUE);
}

void *agx_matrix_add_by_value(AgxMatrix *mat, double val) {
    for (int i = 0; i < mat->size; i++) {
        mat->p_r_nums[i] += val;
    }
}

void *agx_matrix_substract_by_value(AgxMatrix *mat, double val) {
    for (int i = 0; i < mat->size; i++) {
        mat->p_r_nums[i] -= val;
    }
}

void *agx_matrix_multiply_by_value(AgxMatrix *mat, double val) {
    for (int i = 0; i < mat->size; i++) {
        mat->p_r_nums[i] *= val;
    }
}

void *agx_matrix_devide_by_value(AgxMatrix *mat, double val) {
    for (int i = 0; i < mat->size; i++) {
        mat->p_r_nums[i] /= val;
    }
}

AgxMatrix *agx_matrix_new_duplicate_size(AgxMatrix *mat) {
    AgxMatrix *mat_new = agx_matrix_new(mat->r_shape[0], mat->r_shape[1]);
    return mat_new;
}

void *agx_matrix_copy_elements(AgxMatrix *src, AgxMatrix *target) {
    if (src->size == target->size) {
        for (int i = 0; i < target->size; i++) {
            target->p_r_nums[i] = src->p_r_nums[i];
        }
    }
}

void *agx_matrix_copy_shape(AgxMatrix *src, AgxMatrix *target) {
    target->r_shape[0] = src->r_shape[0];
    target->r_shape[1] = src->r_shape[1];
}

void *agx_matrix_transpose(AgxMatrix *mat) {
    AgxMatrix *mat_new = agx_matrix_new(mat->r_shape[1], mat->r_shape[0]);
    for (int i = 0; i < mat->r_shape[0]; i++) {
        for (int j = 0; j < mat->r_shape[1]; j++) {
            mat_new->p_r_nums[agx_matrix_row_col_to_index(mat_new, j, i)] = mat->p_r_nums[agx_matrix_row_col_to_index(mat, i, j)];
        }
    }
    agx_matrix_copy_elements(mat_new, mat);
    agx_matrix_copy_shape(mat_new, mat);
    agx_matrix_delete(mat_new);
}

AgxMatrix *agx_matrix_new_copy(AgxMatrix *mat) {
    AgxMatrix *mat_new = agx_matrix_new_duplicate_size(mat);
    agx_matrix_copy_elements(mat, mat_new);
    return mat_new;
}

AgxMatrix *agx_matrix_new_from_vector(AgxVector *vec) {
    AgxMatrix *mat = agx_matrix_new(1, vec->size);
    for (int i = 0; i < vec->size; i++) {
        mat->p_r_nums[i] = vec->p_r_nums[i];
    }
    return mat;
}

AgxMatrix *agx_matrix_new_identity(int size) {
    AgxMatrix *mat = agx_matrix_new(size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                mat->p_r_nums[agx_matrix_row_col_to_index(mat, i, j)] = 1.;
            } else {
                mat->p_r_nums[agx_matrix_row_col_to_index(mat, i, j)] = 0.;
            }
        }
    }
    return mat;
}

AgxMatrix *agx_matrix_new_zero(int row, int col) {
    AgxMatrix *mat = agx_matrix_new_constant(row, col, 0.);
    return mat;
}

double agx_matrix_row_multiply_col(AgxMatrix *mat1, AgxMatrix *mat2, int row1, int col2) {
    double res = 0;
    if (mat1->r_shape[1] == mat2->r_shape[0]) {
        for (int i = 0; i < mat1->r_shape[1]; i++) {
            res += (mat1->p_r_nums[agx_matrix_row_col_to_index(mat1,row1,i)] * mat2->p_r_nums[agx_matrix_row_col_to_index(mat2, i, col2)]);
        }
        return res;
    }
}

AgxMatrix *agx_matrix_new_multiplication(AgxMatrix *mat1, AgxMatrix *mat2) {
    AgxMatrix *res;
    if (mat1->r_shape[1] == mat2->r_shape[0]) {
        res = agx_matrix_new(mat1->r_shape[0], mat2->r_shape[1]);
        for (int i = 0; i < res->r_shape[0]; i++) {
            for (int j = 0; j < res->r_shape[1]; j++) {
                res->p_r_nums[agx_matrix_row_col_to_index(res, i, j)] = agx_matrix_row_multiply_col(mat1, mat2, i, j);
            }
        }
        return res;
    }
}

AgxVector *agx_vector_new_from_matrix(AgxMatrix *mat) {
    AgxVector *vec = agx_vector_new(mat->size);
    for (int i = 0; i < mat->size; i++) {
        vec->p_r_nums[i] = mat->p_r_nums[i];
    }
    return vec;
}

AgxMatrix *agx_matrix_new_extract_column(AgxMatrix *mat, int col) {
    AgxMatrix *mat_new = agx_matrix_new(mat->r_shape[0],1);
    for (int i = 0; i < mat->r_shape[0]; i++) {
        mat_new->p_r_nums[i] = mat->p_r_nums[agx_matrix_row_col_to_index(mat, i, col)];
    }
    return mat_new;
}

AgxMatrix *agx_matrix_new_extract_row(AgxMatrix *mat, int row) {
    AgxMatrix *mat_new = agx_matrix_new(1,mat->r_shape[1]);
    for (int i = 0; i < mat->r_shape[1]; i++) {
        mat_new->p_r_nums[i] = mat->p_r_nums[agx_matrix_row_col_to_index(mat, row, i)];
    }
    return mat_new;
}

AgxMatrix *agx_matrix_new_extract_row_col(AgxMatrix *mat, int row1, int row2, int col1, int col2) {
    AgxMatrix *mat_new = agx_matrix_new((row2-row1)+1,(col2-col1)+1);
    for (int i = row1, ii = 0; i <= row2, ii < mat_new->r_shape[0]; i++, ii++) {
        for (int j = col1, jj = 0; j <= col2, jj < mat_new->r_shape[1]; j++, jj++) {
            mat_new->p_r_nums[agx_matrix_row_col_to_index(mat_new,ii, jj)] = mat->p_r_nums[agx_matrix_row_col_to_index(mat, i, j)];
        }
    }
    return mat_new;
}

double agx_matrix_min(AgxMatrix *mat) {
    double val;
    val = mat->p_r_nums[0];
    for(int i = 1; i < mat->size; i++) {
        if (val > mat->p_r_nums[i]) {
            val = mat->p_r_nums[i];
        }
    }
    return val;
}

double agx_matrix_max(AgxMatrix *mat) {
    double val;
    val = mat->p_r_nums[0];
    for(int i = 1; i < mat->size; i++) {
        if (val < mat->p_r_nums[i]) {
            val = mat->p_r_nums[i];
        }
    }
    return val;
}
