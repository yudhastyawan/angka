#ifndef __MATRIX_H
#define __MATRIX_H

typedef char * Matrix_String;

typedef struct Matrix {
    double *array;
    int shape[2];
    int size;
} Matrix;

Matrix *Matrix_New(int row, int column);
void Matrix_Delete(Matrix *mat);
void *Matrix_ChangeElements_ByValue(Matrix *mat, double val);
Matrix *Matrix_New_Constant(int row, int column, double val);
Matrix *Matrix_New_Random(int row, int column, double min, double max);
int Matrix_RowCol2Index(Matrix *mat, int row, int col);
void *Matrix_SetItem(Matrix *mat, int row, int col, double val);
double Matrix_GetItem(Matrix *mat, int row, int col);
Matrix_String Matrix_ToString(Matrix *mat, int islong);
void *Matrix_Print(Matrix *mat, int islong);
void *Matrix_QuickPrint(Matrix *mat);
void *Matrix_LongPrint(Matrix *mat);
void *Matrix_Add_ByValue(Matrix *mat, double val);
void *Matrix_Substract_ByValue(Matrix *mat, double val);
void *Matrix_Multiply_ByValue(Matrix *mat, double val);
void *Matrix_Devide_ByValue(Matrix *mat, double val);
Matrix *Matrix_New_DuplicateSize(Matrix *mat);
void *Matrix_CopyElements(Matrix *src, Matrix *target);
void *Matrix_CopyShape(Matrix *src, Matrix *target);
void *Matrix_Transpose(Matrix *mat);
Matrix *Matrix_New_Copy(Matrix *mat);
Matrix *Matrix_New_FromVector(Vector *vec);
Matrix *Matrix_New_Identity(int size);

#endif