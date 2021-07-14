#ifndef __VECTOR_H
#define __VECTOR_H

typedef char * Vector_String;

typedef struct Vector {
    double *array;
    int size;
} Vector;

Vector *Vector_New(int size);
void *Vector_SetItem(Vector *vec, int index, double val);
void *Vector_GetItem(Vector *vec, int index, double *target);
Vector_String Vector_ToString(Vector *vec, int islong);
void Vector_Delete(Vector *vec);
Vector *Vector_New_Random(int size, double min, double max);
void *Vector_Print(Vector *vec, int islong);
void *Vector_Append_Value(Vector *vec, double val);
void *Vector_Append_Vector(Vector *vec_target, Vector *vec_another);
void *Vector_QuickPrint(Vector *vec);
void *Vector_LongPrint(Vector *vec);
void *Vector_Add_ByValue(Vector *vec, double val);
void *Vector_Substract_ByValue(Vector *vec, double val);
void *Vector_Multiply_ByValue(Vector *vec, double val);
void *Vector_Devide_ByValue(Vector *vec, double val);
void *Vector_ChangeElements_ByValue(Vector *vec, double val);
Vector *Vector_New_Constant(int size, double val);
Vector *Vector_New_DuplicateSize(Vector *vec);
void *Vector_CopyElements(Vector *src, Vector *target);
Vector *Vector_New_Copy(Vector *vec);
#endif