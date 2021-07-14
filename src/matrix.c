#include "matrix.h"
#include "standard.h"
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
    return col + row*mat->shape[0];
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
    char *mat_string, *temp_string;
    int mat_length, temp_length;
    int i, j;

    // counting the string length
    mat_length += snprintf(0,0,"shape (,)\n");
    mat_length += snprintf(0,0,"%d", mat->shape[0])+1;
    mat_length += snprintf(0,0,"%d", mat->shape[1])+1;
    if (islong == 1 || (mat->shape[0] <= 5 && mat->shape[1] <= 5)) {
        // [],[],[]
        for (i = 0; i < mat->shape[0]; i++) {
            mat_length += snprintf(0,0,"[]\n");
            for (j = 0; j < mat->shape[1]; j++) {
                mat_length += snprintf(0,0,"%f",mat->array[Matrix_RowCol2Index(mat, i, j)]);
            }
        }
    }
    mat_length += 1;

    // designing the string
    mat_string = malloc(mat_length);
    strcpy(mat_string, "shape (");

    temp_length = snprintf(0,0,"%d", mat->shape[0]) + 1;
    temp_string = malloc(temp_length);
    snprintf(temp_string, temp_length, "%d", mat->shape[0]);
    strcat(mat_string, temp_string);

    strcat(mat_string, ",");

    temp_length = snprintf(0,0,"%d", mat->shape[1]) + 1;
    temp_string = realloc(temp_string, temp_length);
    snprintf(temp_string, temp_length, "%d", mat->shape[0]);
    strcat(mat_string, temp_string);
    strcat(mat_string, ")\n");

    free(temp_string);
    return mat_string;
}

void *Matrix_Print(Matrix *mat, int islong) {
    Matrix_String mat_str = Matrix_ToString(mat, islong);
    printf("%s", mat_str);
    Data_Delete(mat_str);
}
