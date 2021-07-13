#include "vector.h"
#include "standard.h"
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

void *Vector_GetItem(Vector *vec, int index, double *target) {
    if (index < vec->size) {
        *target = vec->array[index];
    } else {
        return NULL;
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
    for(int i = 0; i < vec->size; i++) {
        Vector_SetItem(vec, i, Random(min, max));
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
