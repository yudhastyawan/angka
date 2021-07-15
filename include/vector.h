#ifndef __VECTOR_H
#define __VECTOR_H

typedef char * vectorstring;

typedef struct vector {
    double *array;
    int size;
} vector;

vector *getVectorNew(int size);
void *getVectorSetItem(vector *vec, int index, double val);
double getVectorItem(vector *vec, int index);
vectorstring getVectorToString(vector *vec, int islong);
void getVectorDelete(vector *vec);
vector *getVectorNewRandom(int size, double min, double max);
void *getVectorPrint(vector *vec, int islong);
void *getVectorAppendValue(vector *vec, double val);
void *getVectorAppendVector(vector *vec_target, vector *vec_another);
void *getVectorPrintQuick(vector *vec);
void *getVectorPrintFull(vector *vec);
void *getVectorAddByValue(vector *vec, double val);
void *getVectorSubstractByValue(vector *vec, double val);
void *getVectorMultiplyByValue(vector *vec, double val);
void *getVectorDevideByValue(vector *vec, double val);
void *getVectorChangeAllElementsByValue(vector *vec, double val);
vector *getVectorNewConstant(int size, double val);
vector *getVectorNewDuplicateSize(vector *vec);
void *getVectorCopyElements(vector *src, vector *target);
vector *getVectorNewCopy(vector *vec);
vector *getVectorNewZero(int size);

#endif