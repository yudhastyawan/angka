#include "init.h"
#include "standard.h"
#include "vector.h"
#include <malloc.h>
#include <string.h>

Vector *Vector_New(int size) {
    Vector *vec;
    vec = (Vector *)malloc(sizeof(Vector));
    vec->array = (double *)malloc((size)*sizeof(double));
    vec->size = size;
    return vec;
}

void *Vector_SetItem(Vector *vec, int index, double val) {
    if(index < vec->size) {
        vec->array[index] = val;
    } else {
        return NULL;
    }
}

double Vector_GetItem(Vector *vec, int index) {
    if (index < vec->size) {
        return vec->array[index];
    }
}

Vector_String Vector_ToString(Vector *vec, int islong) {
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

void Vector_Delete(Vector *vec) {
    free(vec->array);
    free(vec);
}

Vector *Vector_New_Random(int size, double min, double max) {
    Vector *vec = Vector_New(size);
    double val;
    for(int i = 0; i < vec->size; i++) {
        val = Random(min, max);
        Vector_SetItem(vec, i, val);
    }
    return vec;
}

void *Vector_Print(Vector *vec, int islong) {
    Vector_String vec_str = Vector_ToString(vec, islong);
    printf("%s", vec_str);
    Data_Delete(vec_str);
}

void *Vector_Append_Value(Vector *vec, double val) {
    vec->array = (double *)realloc(vec->array, (vec->size+1)*sizeof(double));
    vec->array[vec->size] = val;
    vec->size += 1;
}

void *Vector_Append_Vector(Vector *vec_target, Vector *vec_another) {
    vec_target->array = (double *)
        realloc(vec_target->array, (vec_target->size+vec_another->size)
            *sizeof(double));
    for(int i = vec_target->size; i < (vec_target->size + vec_another->size); i++){
        vec_target->array[i] = vec_another->array[i-vec_target->size];
    }
    vec_target->size += vec_another->size;
}

void *Vector_QuickPrint(Vector *vec){
    Vector_Print(vec, 0);
}

void *Vector_LongPrint(Vector *vec){
    Vector_Print(vec, 1);
}

void *Vector_Add_ByValue(Vector *vec, double val) {
    for (int i = 0; i < vec->size; i++) {
        vec->array[i] += val;
    }
}

void *Vector_Substract_ByValue(Vector *vec, double val) {
    for (int i = 0; i < vec->size; i++) {
        vec->array[i] -= val;
    }
}

void *Vector_Multiply_ByValue(Vector *vec, double val) {
    for (int i = 0; i < vec->size; i++) {
        vec->array[i] *= val;
    }
}

void *Vector_Devide_ByValue(Vector *vec, double val) {
    for (int i = 0; i < vec->size; i++) {
        vec->array[i] /= val;
    }
}

void *Vector_ChangeElements_ByValue(Vector *vec, double val) {
    for (int i = 0; i < vec->size; i++) {
        vec->array[i] = val;
    }
}

Vector *Vector_New_Constant(int size, double val) {
    Vector *vec = Vector_New(size);
    Vector_ChangeElements_ByValue(vec, val);
    return vec;
}

Vector *Vector_New_DuplicateSize(Vector *vec) {
    Vector *vec_new = Vector_New(vec->size);
    return vec_new;
}

void *Vector_CopyElements(Vector *src, Vector *target) {
    if (src->size == target->size) {
        for (int i = 0; i < target->size; i++) {
            target->array[i] = src->array[i];
        }
    }
}

Vector *Vector_New_Copy(Vector *vec) {
    Vector *vec_new = Vector_New_DuplicateSize(vec);
    Vector_CopyElements(vec, vec_new);
    return vec_new;
}