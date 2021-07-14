#include "init.h"
#include "standard.h"
#include "vector.h"
#include "matrix.h"
#include <malloc.h>
#include <string.h>

Matrix *Matrix_New(int row, int column) {
    Matrix *mat;
    mat = (Matrix *)malloc(sizeof(Matrix));
    mat->size = row * column;
    mat->shape[0] = row;
    mat->shape[1] = column;
    mat->array = (double *)malloc((mat->size)*sizeof(double));
    return mat;
}

void Matrix_Delete(Matrix *mat) {
    free(mat->array);
    free(mat);
}

void *Matrix_ChangeElements_ByValue(Matrix *mat, double val) {
    for (int i = 0; i < mat->size; i++) {
        mat->array[i] = val;
    }
}

Matrix *Matrix_New_Constant(int row, int column, double val) {
    Matrix *mat = Matrix_New(row, column);
    Matrix_ChangeElements_ByValue(mat, val);
    return mat;
}

Matrix *Matrix_New_Random(int row, int column, double min, double max) {
    Matrix *mat = Matrix_New(row, column);
    for (int i = 0; i < mat->size; i++) {
        mat->array[i] = Random(min, max);
    }
    return mat;
}

int Matrix_RowCol2Index(Matrix *mat, int row, int col) {
    return col + row*mat->shape[1];
}

void *Matrix_SetItem(Matrix *mat, int row, int col, double val) {
    int index = Matrix_RowCol2Index(mat, row, col);
    if (index < mat->size) {
        mat->array[index] = val;
    } else {
        return NULL;
    }
}

double Matrix_GetItem(Matrix *mat, int row, int col) {
    return mat->array[Matrix_RowCol2Index(mat, row, col)];
}

Matrix_String Matrix_ToString(Matrix *mat, int islong) {
    char *mat_string;
    int mat_length;
    int i, j;

    // counting the string length
    mat_length += StringLength_String("shape (,)\n");
    mat_length += StringLength_Integer(mat->shape[0]);
    mat_length += StringLength_Integer(mat->shape[1]);
    if (islong == TRUE || (mat->shape[0] <= 5 && mat->shape[1] <= 5)) {
        // [],[],[]
        for (i = 0; i < mat->shape[0]; i++) {
            mat_length += StringLength_String("[]\n");
            for (j = 0; j < mat->shape[1]; j++) {
                mat_length += StringLength_Double(mat->array[Matrix_RowCol2Index(mat, i, j)]);
                if (j < mat->shape[1] - 1) {
                    mat_length += StringLength_String(", ");
                }
            }
        }
    } 
    else if (islong == FALSE && mat->shape[0] <= 5) {
        for (i = 0; i < mat->shape[0]; i++) {
            mat_length += StringLength_String("[]\n");
            for (j = 0; j < mat->shape[1]; j++) {
                if (j < 4) {
                    mat_length += StringLength_Double(mat->array[Matrix_RowCol2Index(mat, i, j)]);
                    if (j < 3) {
                        mat_length += StringLength_String(", ");
                    } else {
                        mat_length += StringLength_String(",..., ");
                    }
                }
                if (j == (mat->shape[1] - 1)) {
                    mat_length += StringLength_Double(mat->array[Matrix_RowCol2Index(mat, i, j)]);
                }
            }
        }
    }
    else if (islong == FALSE && mat->shape[1] <= 5) {
        for (i = 0; i < mat->shape[0]; i++) {
            if (i < 4 || i == (mat->shape[0]-1)) {
                mat_length += StringLength_String("[]\n");
                for (j = 0; j < mat->shape[1]; j++) {
                    mat_length += StringLength_Double(mat->array[Matrix_RowCol2Index(mat, i, j)]);
                    if (j < mat->shape[1] - 1) {
                        mat_length += StringLength_String(", ");
                    }
                }
                if (i == 3) {
                    mat_length += StringLength_String("\t⋮\n");
                }
            }
        }
    }
    else {
        for (i = 0; i < mat->shape[0]; i++) {
            if (i < 4 || i == (mat->shape[0]-1)) {
                mat_length += StringLength_String("[]\n");
                for (j = 0; j < mat->shape[1]; j++) {
                    if (j < 4) {
                        mat_length += StringLength_Double(mat->array[Matrix_RowCol2Index(mat, i, j)]);
                        if (j < 3) {
                            mat_length += StringLength_String(", ");
                        } else {
                            mat_length += StringLength_String(",..., ");
                        }
                    }
                    if (j == (mat->shape[1] - 1)) {
                        mat_length += StringLength_Double(mat->array[Matrix_RowCol2Index(mat, i, j)]);
                    }
                }
                if (i == 3) {
                    mat_length += StringLength_String("\t⋮\n");
                }
            }
        }
    }
    
    mat_length += 1;

    // designing the string
    mat_string = malloc(mat_length);
    strcpy(mat_string, "shape (");
    String_Append_Integer(mat_string, mat->shape[0], FALSE);
    strcat(mat_string, ",");
    String_Append_Integer(mat_string, mat->shape[1], FALSE);
    strcat(mat_string, ")\n");
    if (islong == TRUE || (mat->shape[0] <= 5 && mat->shape[1] <= 5)) {
        for (i = 0; i < mat->shape[0]; i++) {
            strcat(mat_string, "[");
            for (j = 0; j < mat->shape[1]; j++) {
                String_Append_Double(mat_string, mat->array[Matrix_RowCol2Index(mat, i, j)], FALSE);
                if (j < mat->shape[1] - 1) {
                    strcat(mat_string, ", ");
                }
            }
            strcat(mat_string, "]\n");
        }
    }
    else if (islong == FALSE && mat->shape[0] <= 5) {
        for (i = 0; i < mat->shape[0]; i++) {
            strcat(mat_string, "[");
            for (j = 0; j < mat->shape[1]; j++) {
                if (j < 4) {
                    String_Append_Double(mat_string, mat->array[Matrix_RowCol2Index(mat, i, j)], FALSE);
                    if (j < 3) {
                        strcat(mat_string, ", ");
                    } else {
                        strcat(mat_string, ",..., ");
                    }
                }
                if (j == (mat->shape[1] - 1)) {
                    String_Append_Double(mat_string, mat->array[Matrix_RowCol2Index(mat, i, j)], FALSE);
                }
            }
            strcat(mat_string, "]\n");
        }
    }
    else if (islong == FALSE && mat->shape[1] <= 5) {
        for (i = 0; i < mat->shape[0]; i++) {
            if (i < 4 || i == (mat->shape[0]-1)) {
                strcat(mat_string, "[");
                for (j = 0; j < mat->shape[1]; j++) {
                    String_Append_Double(mat_string, mat->array[Matrix_RowCol2Index(mat, i, j)], FALSE);
                    if (j < mat->shape[1] - 1) {
                        strcat(mat_string, ", ");
                    }
                }
                strcat(mat_string, "]\n");
                if (i == 3) {
                    strcat(mat_string, "\t⋮\n");
                }
            }
        }
    }
    else {
        for (i = 0; i < mat->shape[0]; i++) {
            if (i < 4 || i == (mat->shape[0]-1)) {
                strcat(mat_string, "[");
                for (j = 0; j < mat->shape[1]; j++) {
                    if (j < 4) {
                        String_Append_Double(mat_string, mat->array[Matrix_RowCol2Index(mat, i, j)], FALSE);
                        if (j < 3) {
                            strcat(mat_string, ", ");
                        } else {
                            strcat(mat_string, ",..., ");
                        }
                    }
                    if (j == (mat->shape[1] - 1)) {
                        String_Append_Double(mat_string, mat->array[Matrix_RowCol2Index(mat, i, j)], FALSE);
                    }
                }
                strcat(mat_string, "]\n");
                if (i == 3) {
                    strcat(mat_string, "\t⋮\n");
                }
            }
        }
    }

    return mat_string;
}

void *Matrix_Print(Matrix *mat, int islong) {
    Matrix_String mat_str = Matrix_ToString(mat, islong);
    printf("%s", mat_str);
    Data_Delete(mat_str);
}

void *Matrix_QuickPrint(Matrix *mat) {
    Matrix_Print(mat, FALSE);
}

void *Matrix_LongPrint(Matrix *mat) {
    Matrix_Print(mat, TRUE);
}

void *Matrix_Add_ByValue(Matrix *mat, double val) {
    for (int i = 0; i < mat->size; i++) {
        mat->array[i] += val;
    }
}

void *Matrix_Substract_ByValue(Matrix *mat, double val) {
    for (int i = 0; i < mat->size; i++) {
        mat->array[i] -= val;
    }
}

void *Matrix_Multiply_ByValue(Matrix *mat, double val) {
    for (int i = 0; i < mat->size; i++) {
        mat->array[i] *= val;
    }
}

void *Matrix_Devide_ByValue(Matrix *mat, double val) {
    for (int i = 0; i < mat->size; i++) {
        mat->array[i] /= val;
    }
}

Matrix *Matrix_New_DuplicateSize(Matrix *mat) {
    Matrix *mat_new = Matrix_New(mat->shape[0], mat->shape[1]);
    return mat_new;
}

void *Matrix_CopyElements(Matrix *src, Matrix *target) {
    if (src->size == target->size) {
        for (int i = 0; i < target->size; i++) {
            target->array[i] = src->array[i];
        }
    }
}

void *Matrix_CopyShape(Matrix *src, Matrix *target) {
    target->shape[0] = src->shape[0];
    target->shape[1] = src->shape[1];
}

void *Matrix_Transpose(Matrix *mat) {
    Matrix *mat_new = Matrix_New(mat->shape[1], mat->shape[0]);
    for (int i = 0; i < mat->shape[0]; i++) {
        for (int j = 0; j < mat->shape[1]; j++) {
            mat_new->array[Matrix_RowCol2Index(mat_new, j, i)] = mat->array[Matrix_RowCol2Index(mat, i, j)];
        }
    }
    Matrix_CopyElements(mat_new, mat);
    Matrix_CopyShape(mat_new, mat);
    Matrix_Delete(mat_new);
}

Matrix *Matrix_New_Copy(Matrix *mat) {
    Matrix *mat_new = Matrix_New_DuplicateSize(mat);
    Matrix_CopyElements(mat, mat_new);
    return mat_new;
}

Matrix *Matrix_New_FromVector(Vector *vec) {
    Matrix *mat = Matrix_New(1, vec->size);
    for (int i = 0; i < vec->size; i++) {
        mat->array[i] = vec->array[i];
    }
    return mat;
}

Matrix *Matrix_New_Identity(int size) {
    Matrix *mat = Matrix_New(size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                mat->array[Matrix_RowCol2Index(mat, i, j)] = 1.;
            } else {
                mat->array[Matrix_RowCol2Index(mat, i, j)] = 0.;
            }
        }
    }
    return mat;
}