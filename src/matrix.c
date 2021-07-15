#include "init.h"
#include "standard.h"
#include "vector.h"
#include "matrix.h"
#include <malloc.h>
#include <string.h>

matrix *getMatrixNew(int row, int column) {
    matrix *mat;
    mat = (matrix *)malloc(sizeof(matrix));
    mat->size = row * column;
    mat->shape[0] = row;
    mat->shape[1] = column;
    mat->array = (double *)malloc((mat->size)*sizeof(double));
    return mat;
}

void getMatrixDelete(matrix *mat) {
    free(mat->array);
    free(mat);
}

void *getMatrixChangeAllElementsByValue(matrix *mat, double val) {
    for (int i = 0; i < mat->size; i++) {
        mat->array[i] = val;
    }
}

matrix *getMatrixNewConstant(int row, int column, double val) {
    matrix *mat = getMatrixNew(row, column);
    getMatrixChangeAllElementsByValue(mat, val);
    return mat;
}

matrix *getMatrixNewRandom(int row, int column, double min, double max) {
    matrix *mat = getMatrixNew(row, column);
    for (int i = 0; i < mat->size; i++) {
        mat->array[i] = getRandom(min, max);
    }
    return mat;
}

int getMatrixRowColToIndex(matrix *mat, int row, int col) {
    return col + row*mat->shape[1];
}

void *getMatrixSetItem(matrix *mat, int row, int col, double val) {
    int index = getMatrixRowColToIndex(mat, row, col);
    if (index < mat->size) {
        mat->array[index] = val;
    } else {
        return NULL;
    }
}

double getMatrixItem(matrix *mat, int row, int col) {
    return mat->array[getMatrixRowColToIndex(mat, row, col)];
}

matrixstring getMatrixToString(matrix *mat, int islong) {
    char *mat_string;
    int mat_length;
    int i, j;

    // counting the string length
    mat_length += getStringLengthString("shape (,)\n");
    mat_length += getStringLengthInteger(mat->shape[0]);
    mat_length += getStringLengthInteger(mat->shape[1]);
    if (islong == TRUE || (mat->shape[0] <= 5 && mat->shape[1] <= 5)) {
        // [],[],[]
        for (i = 0; i < mat->shape[0]; i++) {
            mat_length += getStringLengthString("[]\n");
            for (j = 0; j < mat->shape[1]; j++) {
                mat_length += getStringLengthDouble(mat->array[getMatrixRowColToIndex(mat, i, j)]);
                if (j < mat->shape[1] - 1) {
                    mat_length += getStringLengthString(", ");
                }
            }
        }
    } 
    else if (islong == FALSE && mat->shape[0] <= 5) {
        for (i = 0; i < mat->shape[0]; i++) {
            mat_length += getStringLengthString("[]\n");
            for (j = 0; j < mat->shape[1]; j++) {
                if (j < 4) {
                    mat_length += getStringLengthDouble(mat->array[getMatrixRowColToIndex(mat, i, j)]);
                    if (j < 3) {
                        mat_length += getStringLengthString(", ");
                    } else {
                        mat_length += getStringLengthString(",..., ");
                    }
                }
                if (j == (mat->shape[1] - 1)) {
                    mat_length += getStringLengthDouble(mat->array[getMatrixRowColToIndex(mat, i, j)]);
                }
            }
        }
    }
    else if (islong == FALSE && mat->shape[1] <= 5) {
        for (i = 0; i < mat->shape[0]; i++) {
            if (i < 4 || i == (mat->shape[0]-1)) {
                mat_length += getStringLengthString("[]\n");
                for (j = 0; j < mat->shape[1]; j++) {
                    mat_length += getStringLengthDouble(mat->array[getMatrixRowColToIndex(mat, i, j)]);
                    if (j < mat->shape[1] - 1) {
                        mat_length += getStringLengthString(", ");
                    }
                }
                if (i == 3) {
                    mat_length += getStringLengthString("\t⋮\n");
                }
            }
        }
    }
    else {
        for (i = 0; i < mat->shape[0]; i++) {
            if (i < 4 || i == (mat->shape[0]-1)) {
                mat_length += getStringLengthString("[]\n");
                for (j = 0; j < mat->shape[1]; j++) {
                    if (j < 4) {
                        mat_length += getStringLengthDouble(mat->array[getMatrixRowColToIndex(mat, i, j)]);
                        if (j < 3) {
                            mat_length += getStringLengthString(", ");
                        } else {
                            mat_length += getStringLengthString(",..., ");
                        }
                    }
                    if (j == (mat->shape[1] - 1)) {
                        mat_length += getStringLengthDouble(mat->array[getMatrixRowColToIndex(mat, i, j)]);
                    }
                }
                if (i == 3) {
                    mat_length += getStringLengthString("\t⋮\n");
                }
            }
        }
    }
    
    mat_length += 1;

    // designing the string
    mat_string = malloc(mat_length);
    strcpy(mat_string, "shape (");
    getStringAppendInteger(mat_string, mat->shape[0], FALSE);
    strcat(mat_string, ",");
    getStringAppendInteger(mat_string, mat->shape[1], FALSE);
    strcat(mat_string, ")\n");
    if (islong == TRUE || (mat->shape[0] <= 5 && mat->shape[1] <= 5)) {
        for (i = 0; i < mat->shape[0]; i++) {
            strcat(mat_string, "[");
            for (j = 0; j < mat->shape[1]; j++) {
                getStringAppendDouble(mat_string, mat->array[getMatrixRowColToIndex(mat, i, j)], FALSE);
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
                    getStringAppendDouble(mat_string, mat->array[getMatrixRowColToIndex(mat, i, j)], FALSE);
                    if (j < 3) {
                        strcat(mat_string, ", ");
                    } else {
                        strcat(mat_string, ",..., ");
                    }
                }
                if (j == (mat->shape[1] - 1)) {
                    getStringAppendDouble(mat_string, mat->array[getMatrixRowColToIndex(mat, i, j)], FALSE);
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
                    getStringAppendDouble(mat_string, mat->array[getMatrixRowColToIndex(mat, i, j)], FALSE);
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
                        getStringAppendDouble(mat_string, mat->array[getMatrixRowColToIndex(mat, i, j)], FALSE);
                        if (j < 3) {
                            strcat(mat_string, ", ");
                        } else {
                            strcat(mat_string, ",..., ");
                        }
                    }
                    if (j == (mat->shape[1] - 1)) {
                        getStringAppendDouble(mat_string, mat->array[getMatrixRowColToIndex(mat, i, j)], FALSE);
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

void *getMatrixPrint(matrix *mat, int islong) {
    matrixstring mat_str = getMatrixToString(mat, islong);
    printf("%s", mat_str);
    getDataDelete(mat_str);
}

void *getMatrixPrintQuick(matrix *mat) {
    getMatrixPrint(mat, FALSE);
}

void *getMatrixPrintFull(matrix *mat) {
    getMatrixPrint(mat, TRUE);
}

void *getMatrixAddByValue(matrix *mat, double val) {
    for (int i = 0; i < mat->size; i++) {
        mat->array[i] += val;
    }
}

void *getMatrixSubstractByValue(matrix *mat, double val) {
    for (int i = 0; i < mat->size; i++) {
        mat->array[i] -= val;
    }
}

void *getMatrixMultiplyByValue(matrix *mat, double val) {
    for (int i = 0; i < mat->size; i++) {
        mat->array[i] *= val;
    }
}

void *getMatrixDevideByValue(matrix *mat, double val) {
    for (int i = 0; i < mat->size; i++) {
        mat->array[i] /= val;
    }
}

matrix *getMatrixNewDuplicateSize(matrix *mat) {
    matrix *mat_new = getMatrixNew(mat->shape[0], mat->shape[1]);
    return mat_new;
}

void *getMatrixCopyElements(matrix *src, matrix *target) {
    if (src->size == target->size) {
        for (int i = 0; i < target->size; i++) {
            target->array[i] = src->array[i];
        }
    }
}

void *getMatrixCopyShape(matrix *src, matrix *target) {
    target->shape[0] = src->shape[0];
    target->shape[1] = src->shape[1];
}

void *getMatrixTranspose(matrix *mat) {
    matrix *mat_new = getMatrixNew(mat->shape[1], mat->shape[0]);
    for (int i = 0; i < mat->shape[0]; i++) {
        for (int j = 0; j < mat->shape[1]; j++) {
            mat_new->array[getMatrixRowColToIndex(mat_new, j, i)] = mat->array[getMatrixRowColToIndex(mat, i, j)];
        }
    }
    getMatrixCopyElements(mat_new, mat);
    getMatrixCopyShape(mat_new, mat);
    getMatrixDelete(mat_new);
}

matrix *getMatrixNewCopy(matrix *mat) {
    matrix *mat_new = getMatrixNewDuplicateSize(mat);
    getMatrixCopyElements(mat, mat_new);
    return mat_new;
}

matrix *getMatrixNewFromVector(vector *vec) {
    matrix *mat = getMatrixNew(1, vec->size);
    for (int i = 0; i < vec->size; i++) {
        mat->array[i] = vec->array[i];
    }
    return mat;
}

matrix *getMatrixNewIdentity(int size) {
    matrix *mat = getMatrixNew(size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                mat->array[getMatrixRowColToIndex(mat, i, j)] = 1.;
            } else {
                mat->array[getMatrixRowColToIndex(mat, i, j)] = 0.;
            }
        }
    }
    return mat;
}

matrix *getMatrixNewZero(int row, int col) {
    matrix *mat = getMatrixNewConstant(row, col, 0.);
    return mat;
}