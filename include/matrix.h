#ifndef __MATRIX_H
#define __MATRIX_H

typedef char * matrixstring;

typedef struct matrix {
    double *array;
    int shape[2];
    int size;
} matrix;

matrix *getMatrixNew(int row, int column);
void getMatrixDelete(matrix *mat);
void *getMatrixChangeAllElementsByValue(matrix *mat, double val);
matrix *getMatrixNewConstant(int row, int column, double val);
matrix *getMatrixNewRandom(int row, int column, double min, double max);
int getMatrixRowColToIndex(matrix *mat, int row, int col);
void *getMatrixSetItem(matrix *mat, int row, int col, double val);
double getMatrixItem(matrix *mat, int row, int col);
matrixstring getMatrixToString(matrix *mat, int islong);
void *getMatrixPrint(matrix *mat, int islong);
void *getMatrixPrint(matrix *mat, int islong);
void *getMatrixPrintQuick(matrix *mat);
void *getMatrixPrintFull(matrix *mat);
void *getMatrixAddByValue(matrix *mat, double val);
void *getMatrixSubstractByValue(matrix *mat, double val);
void *getMatrixMultiplyByValue(matrix *mat, double val);
void *getMatrixDevideByValue(matrix *mat, double val);
matrix *getMatrixNewDuplicateSize(matrix *mat);
void *getMatrixCopyElements(matrix *src, matrix *target);
void *getMatrixCopyShape(matrix *src, matrix *target);
void *getMatrixTranspose(matrix *mat);
matrix *getMatrixNewCopy(matrix *mat);
matrix *getMatrixNewFromVector(vector *vec);
matrix *getMatrixNewIdentity(int size);
matrix *getMatrixNewZero(int row, int col);

#endif