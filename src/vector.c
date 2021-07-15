#include "init.h"
#include "standard.h"
#include "vector.h"
#include <malloc.h>
#include <string.h>

vector *getVectorNew(int size) {
    vector *vec;
    vec = (vector *)malloc(sizeof(vector));
    vec->array = (double *)malloc((size)*sizeof(double));
    vec->size = size;
    return vec;
}

void *getVectorSetItem(vector *vec, int index, double val) {
    if(index < vec->size) {
        vec->array[index] = val;
    } else {
        return NULL;
    }
}

double getVectorItem(vector *vec, int index) {
    if (index < vec->size) {
        return vec->array[index];
    }
}

vectorstring getVectorToString(vector *vec, int islong) {
    char *vec_string;
    int vec_length, temp_length;
    int i;

    // counting the string length
    vec_length += snprintf(0,0,"%d", vec->size)+1; // size
    vec_length += snprintf(0,0,"[")*3; // []' '
    vec_length += snprintf(0,0,"\n");
    if (islong == 1 || vec->size <= 5){
        vec_length += snprintf(0,0,", ")*(vec->size-1); // ,' '
        for (i = 0; i < vec->size; i++) {
            vec_length += snprintf(0,0,"%f",vec->array[i]);
        }
    } else {
        vec_length += snprintf(0,0,", ")*4; // ,' '
        vec_length += snprintf(0,0,",..."); // ,' '
        for (i = 0; i < vec->size; i++) {
            if (i < 4) {
                vec_length += snprintf(0,0,"%f",vec->array[i]);
            }
            if (i == (vec->size-1)) {
                vec_length += snprintf(0,0,"%f",vec->array[i]);
            }
        }
    }
    vec_length += 1;

    // designing the string
    vec_string = malloc(vec_length);
    temp_length = snprintf(0,0,"%d",vec->size)+1;
    char *temp_string = malloc(temp_length);
    snprintf(temp_string, temp_length, "%d", vec->size);
    strcpy(vec_string, temp_string);
    free(temp_string);
    strcat(vec_string, " [");
    if (islong == 1 || vec->size <= 5) {
        for (i = 0; i < vec->size; i++) {
            temp_length = snprintf(0,0,"%f",vec->array[i]);
            char *temp_string = malloc(temp_length);
            snprintf(temp_string, temp_length, "%f", vec->array[i]);
            strcat(vec_string, temp_string);
            if (i < (vec->size-1)) {
                strcat(vec_string, ", ");
            }
            free(temp_string);
        }
    } else {
        for (i = 0; i < vec->size; i++) {
            if (i < 4) {
                temp_length = snprintf(0,0,"%f",vec->array[i]);
                char *temp_string = malloc(temp_length);
                snprintf(temp_string, temp_length, "%f", vec->array[i]);
                strcat(vec_string, temp_string);
                if (i < 3) {
                    strcat(vec_string, ", ");
                } else {
                    strcat(vec_string, ",..., ");
                }
                free(temp_string);
            }
            if (i == (vec->size-1)) {
                temp_length = snprintf(0,0,"%f",vec->array[i]);
                char *temp_string = malloc(temp_length);
                snprintf(temp_string, temp_length, "%f", vec->array[i]);
                strcat(vec_string, temp_string);
                free(temp_string);
            }
        }
    }
    strcat(vec_string, "]\n");
    return vec_string;
}

void getVectorDelete(vector *vec) {
    free(vec->array);
    free(vec);
}

vector *getVectorNewRandom(int size, double min, double max) {
    vector *vec = getVectorNew(size);
    double val;
    for(int i = 0; i < vec->size; i++) {
        val = getRandom(min, max);
        getVectorSetItem(vec, i, val);
    }
    return vec;
}

void *getVectorPrint(vector *vec, int islong) {
    vectorstring vec_str = getVectorToString(vec, islong);
    printf("%s", vec_str);
    getDataDelete(vec_str);
}

void *getVectorAppendValue(vector *vec, double val) {
    vec->array = (double *)realloc(vec->array, (vec->size+1)*sizeof(double));
    vec->array[vec->size] = val;
    vec->size += 1;
}

void *getVectorAppendVector(vector *vec_target, vector *vec_another) {
    vec_target->array = (double *)
        realloc(vec_target->array, (vec_target->size+vec_another->size)
            *sizeof(double));
    for(int i = vec_target->size; i < (vec_target->size + vec_another->size); i++){
        vec_target->array[i] = vec_another->array[i-vec_target->size];
    }
    vec_target->size += vec_another->size;
}

void *getVectorPrintQuick(vector *vec){
    getVectorPrint(vec, 0);
}

void *getVectorPrintFull(vector *vec){
    getVectorPrint(vec, 1);
}

void *getVectorAddByValue(vector *vec, double val) {
    for (int i = 0; i < vec->size; i++) {
        vec->array[i] += val;
    }
}

void *getVectorSubstractByValue(vector *vec, double val) {
    for (int i = 0; i < vec->size; i++) {
        vec->array[i] -= val;
    }
}

void *getVectorMultiplyByValue(vector *vec, double val) {
    for (int i = 0; i < vec->size; i++) {
        vec->array[i] *= val;
    }
}

void *getVectorDevideByValue(vector *vec, double val) {
    for (int i = 0; i < vec->size; i++) {
        vec->array[i] /= val;
    }
}

void *getVectorChangeAllElementsByValue(vector *vec, double val) {
    for (int i = 0; i < vec->size; i++) {
        vec->array[i] = val;
    }
}

vector *getVectorNewConstant(int size, double val) {
    vector *vec = getVectorNew(size);
    getVectorChangeAllElementsByValue(vec, val);
    return vec;
}

vector *getVectorNewDuplicateSize(vector *vec) {
    vector *vec_new = getVectorNew(vec->size);
    return vec_new;
}

void *getVectorCopyElements(vector *src, vector *target) {
    if (src->size == target->size) {
        for (int i = 0; i < target->size; i++) {
            target->array[i] = src->array[i];
        }
    }
}

vector *getVectorNewCopy(vector *vec) {
    vector *vec_new = getVectorNewDuplicateSize(vec);
    getVectorCopyElements(vec, vec_new);
    return vec_new;
}

vector *getVectorNewZero(int size) {
    return getVectorNewConstant(size, 0.);
}