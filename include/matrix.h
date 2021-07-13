#ifndef __MATRIX_H
#define __MATRIX_H

typedef struct Matrix {
    double *array;
    int shape[2];
    int size;
} Matrix;

#endif