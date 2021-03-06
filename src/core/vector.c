#include "init.h"
#include "standard.h"
#include "vector.h"
#include <malloc.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <stdio.h>

AgxVector *agx_vector_new(int size) {
    AgxVector *vec;
    vec = malloc(sizeof(AgxVector));
    if (vec == NULL) {
        fprintf(stderr, "vec cannot be allocated\n");
        return NULL;
    }
    vec->p_r_nums = malloc((size)*sizeof(double));
    if (vec->p_r_nums == NULL) {
        fprintf(stderr, "vec->p_r_nums cannot be allocated\n");
        return NULL;
    }
    vec->size = size;
    return vec;
}

int agx_vector_set_item(AgxVector *vec, int index, double val) {
    if(index < vec->size) {
        vec->p_r_nums[index] = val;
    } else {
        fprintf(stderr, "index exceeds the size of vector\n");
        return -1;
    }
    return 0;
}

int agx_vector_get_item(AgxVector *vec, int index, double *output) {
    if (index < vec->size) {
        *output = vec->p_r_nums[index];
    } else {
        fprintf(stderr, "index exceeds the size of array\n");
        return -1;
    }
    return 0;
}

p_vectorString_t agx_vector_to_string(AgxVector *vec, int islong) {
    char *vec_string;
    int vec_length, temp_length;
    int i;

    // counting the string length
    vec_length = snprintf(0,0,"%d", vec->size)+1; // size
    vec_length += snprintf(0,0,"[")*3; // []' '
    vec_length += snprintf(0,0,"\n");
    if (islong == 1 || vec->size <= 5){
        vec_length += snprintf(0,0,", ")*(vec->size-1); // ,' '
        for (i = 0; i < vec->size; i++) {
            vec_length += snprintf(0,0,"%f",vec->p_r_nums[i]);
        }
    } else {
        vec_length += snprintf(0,0,", ")*4; // ,' '
        vec_length += snprintf(0,0,",..."); // ,' '
        for (i = 0; i < vec->size; i++) {
            if (i < 4) {
                vec_length += snprintf(0,0,"%f",vec->p_r_nums[i]);
            }
            if (i == (vec->size-1)) {
                vec_length += snprintf(0,0,"%f",vec->p_r_nums[i]);
            }
        }
    }
    vec_length += 1;

    // designing the string
    vec_string = malloc(vec_length);
    if (vec_string == NULL) {
        fprintf(stderr, "vec_string cannot be allocated\n");
        return NULL;
    }

    temp_length = snprintf(0,0,"%d",vec->size)+1;
    char *temp_string = malloc(temp_length);
    if (temp_string == NULL) {
        fprintf(stderr, "temp_string cannot be allocated\n");
        return NULL;
    }

    snprintf(temp_string, temp_length, "%d", vec->size);
    strcpy(vec_string, temp_string);
    free(temp_string);
    temp_string = NULL;

    strcat(vec_string, " [");
    if (islong == 1 || vec->size <= 5) {
        for (i = 0; i < vec->size; i++) {
            temp_length = snprintf(0,0,"%f",vec->p_r_nums[i]);
            char *temp_string = malloc(temp_length);
            if (temp_string == NULL) {
               fprintf(stderr, "temp_string cannot be allocated\n");
               return NULL;
            }
            snprintf(temp_string, temp_length, "%f", vec->p_r_nums[i]);
            strcat(vec_string, temp_string);
            if (i < (vec->size-1)) {
                strcat(vec_string, ", ");
            }
            free(temp_string);
            temp_string = NULL;
        }
    } else {
        for (i = 0; i < vec->size; i++) {
            if (i < 4) {
                temp_length = snprintf(0,0,"%f",vec->p_r_nums[i]);
                char *temp_string = malloc(temp_length);
                if (temp_string == NULL) {
                    fprintf(stderr, "temp_string cannot be allocated\n");
                    return NULL;
                }
                snprintf(temp_string, temp_length, "%f", vec->p_r_nums[i]);
                strcat(vec_string, temp_string);
                if (i < 3) {
                    strcat(vec_string, ", ");
                } else {
                    strcat(vec_string, ",..., ");
                }
                free(temp_string);
                temp_string = NULL;
            }
            if (i == (vec->size-1)) {
                temp_length = snprintf(0,0,"%f",vec->p_r_nums[i]);
                char *temp_string = malloc(temp_length);
                if (temp_string == NULL) {
                    fprintf(stderr, "temp_string cannot be allocated\n");
                    return NULL;
                }
                snprintf(temp_string, temp_length, "%f", vec->p_r_nums[i]);
                strcat(vec_string, temp_string);
                free(temp_string);
                temp_string = NULL;
            }
        }
    }
    strcat(vec_string, "]\n");
    return vec_string;
}

void agx_vector_delete(AgxVector **vec) {
    if (*vec == NULL || (*vec)->p_r_nums == NULL) {
        return;
    }
    free((*vec)->p_r_nums);
    (*vec)->p_r_nums = NULL;
    free(*vec);
    *vec = NULL;
}

AgxVector *agx_vector_new_random(int size, double min, double max) {
    AgxVector *vec = agx_vector_new(size);
    if (vec == NULL) {
        fprintf(stderr, "vec cannot be allocated\n");
        return NULL;
    }
    double val;
    for(int i = 0; i < vec->size; i++) {
        val = agx_random(min, max);
        agx_vector_set_item(vec, i, val);
    }
    return vec;
}

AgxVector *agx_vector_new_from_array(double *ndarray_in, int size) {
    AgxVector *vec = agx_vector_new(size);
    if (vec == NULL) {
        fprintf(stderr, "vec cannot be allocated\n");
        return NULL;
    }
    for(int i = 0; i < vec->size; i++) {
        vec->p_r_nums[i] = ndarray_in[i];
    }
    return vec;
}

void agx_vector_to_array(AgxVector *vec, double **ndarray_out, int *size) {
    *ndarray_out = vec->p_r_nums;
    *size = vec->size;
}

int agx_vector_print(AgxVector *vec, int islong) {
    p_vectorString_t vec_str = agx_vector_to_string(vec, islong);
    if (vec_str == NULL) {
        fprintf(stderr, "vec_str cannot be allocated\n");
        return -1;
    }
    printf("%s", vec_str);
    agx_data_delete(vec_str);
    vec_str = NULL;
    return 0;
}

int agx_vector_append_value(AgxVector *vec, double val) {
    vec->p_r_nums = realloc(vec->p_r_nums, (vec->size+1)*sizeof(double));
    if (vec->p_r_nums == NULL) {
        fprintf(stderr, "vec->p_r_nums cannot be allocated\n");
        return -1;
    }
    vec->p_r_nums[vec->size] = val;
    vec->size += 1;
    return 0;
}

int agx_vector_append_vector(AgxVector *vec_target, AgxVector *vec_another) {
    vec_target->p_r_nums = realloc(vec_target->p_r_nums, 
        (vec_target->size+vec_another->size)*sizeof(double));
    if (vec_target->p_r_nums == NULL) {
        fprintf(stderr, "vec_target->p_r_nums cannot be allocated\n");
        return -1;
    }
    for(int i = vec_target->size; i < (vec_target->size + vec_another->size); i++){
        vec_target->p_r_nums[i] = vec_another->p_r_nums[i-vec_target->size];
    }
    vec_target->size += vec_another->size;
    return 0;
}

int agx_vector_print_partial(AgxVector *vec){
    if (agx_vector_print(vec, 0) != 0) {
        fprintf(stderr, "agx_vector_print error\n");
        return -1;
    }
    return 0;
}

int agx_vector_print_full(AgxVector *vec){
    if (agx_vector_print(vec, 1) != 0) {
        fprintf(stderr, "agx_vector_print error\n");
        return -1;
    }
    return 0;
}

int agx_vector_add_by_value(AgxVector *vec, double val) {
    if (vec == NULL) {
        fprintf(stderr, "vec is NULL\n");
        return -1;
    }
    for (int i = 0; i < vec->size; i++) {
        vec->p_r_nums[i] += val;
    }
    return 0;
}

int agx_vector_substract_by_value(AgxVector *vec, double val) {
    if (vec == NULL) {
        fprintf(stderr, "vec is NULL\n");
        return -1;
    }
    for (int i = 0; i < vec->size; i++) {
        vec->p_r_nums[i] -= val;
    }
    return 0;
}

int agx_vector_multiply_by_value(AgxVector *vec, double val) {
    if (vec == NULL) {
        fprintf(stderr, "vec is NULL\n");
        return -1;
    }
    for (int i = 0; i < vec->size; i++) {
        vec->p_r_nums[i] *= val;
    }
    return 0;
}

int agx_vector_divide_by_value(AgxVector *vec, double val) {
    if (vec == NULL) {
        fprintf(stderr, "vec is NULL\n");
        return -1;
    }
    for (int i = 0; i < vec->size; i++) {
        vec->p_r_nums[i] /= val;
    }
    return 0;
}

int agx_vector_change_elements_by_value(AgxVector *vec, double val) {
    if (vec == NULL) {
        fprintf(stderr, "vec is NULL\n");
        return -1;
    }
    for (int i = 0; i < vec->size; i++) {
        vec->p_r_nums[i] = val;
    }
    return 0;
}

AgxVector *agx_vector_new_constant(int size, double val) {
    AgxVector *vec = agx_vector_new(size);
    if (vec == NULL) {
        fprintf(stderr, "vec cannot be allocated\n");
        return NULL;
    }
    agx_vector_change_elements_by_value(vec, val);
    return vec;
}

AgxVector *agx_vector_new_duplicate_size(AgxVector *vec) {
    AgxVector *vec_new = agx_vector_new(vec->size);
    if (vec_new == NULL) {
        fprintf(stderr, "vec_new cannot be allocated\n");
        return NULL;
    }
    return vec_new;
}

int agx_vector_copy_elements(AgxVector *src, AgxVector *target) {
    if (src->size == target->size) {
        for (int i = 0; i < target->size; i++) {
            target->p_r_nums[i] = src->p_r_nums[i];
        }
    } else {
        fprintf(stderr, "src and target are not the same size\n");
        return -1;
    }
    return 0;
}

AgxVector *agx_vector_new_copy(AgxVector *vec) {
    AgxVector *vec_new = agx_vector_new_duplicate_size(vec);
    if (vec_new == NULL) {
        fprintf(stderr, "vec_new cannot be allocated\n");
        return NULL;
    }
    agx_vector_copy_elements(vec, vec_new);
    return vec_new;
}

AgxVector *agx_vector_new_zero(int size) {
    AgxVector *vec = agx_vector_new_constant(size, 0.);
    if (vec == NULL) {
        fprintf(stderr, "vec cannot be allocated\n");
        return NULL;
    }
    return vec;
}

AgxVector *agx_vector_new_linspace(double min, double max, int size) {
    AgxVector *vec = agx_vector_new(size);
    if (vec == NULL) {
        fprintf(stderr, "vec is NULL\n");
        return NULL;
    }
    for(int i = 0; i < size; i++) {
        vec->p_r_nums[i] = (min + (max-min)*((double)i/size));
    }
    return vec;
}

AgxVector *agx_vector_new_arange(int min, int step, int max) {
    int size = 0;
    for (int i = min; i <= max; i += step) {
        size++;
    }
    AgxVector *vec = agx_vector_new(size);
    if (vec == NULL) {
        fprintf(stderr, "vec is NULL\n");
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        vec->p_r_nums[i] = (double)(min + (step*i));
    }
    return vec;
}

AgxVector *agx_vector_new_arange_double(double min, double step, double max) {
    int size = 0;
    for (double i = min; i <= max; i += step) {
        size++;
    }
    AgxVector *vec = agx_vector_new(size);
    if (vec == NULL) {
        fprintf(stderr, "vec is NULL\n");
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        vec->p_r_nums[i] = (double)(min + (step*i));
    }
    return vec;
}

double agx_vector_min(AgxVector *vec) {
    double val;
    val = vec->p_r_nums[0];
    for(int i = 1; i < vec->size; i++) {
        if (val > vec->p_r_nums[i]) {
            val = vec->p_r_nums[i];
        }
    }
    return val;
}

double agx_vector_max(AgxVector *vec) {
    double val;
    val = vec->p_r_nums[0];
    for(int i = 1; i < vec->size; i++) {
        if (val < vec->p_r_nums[i]) {
            val = vec->p_r_nums[i];
        }
    }
    return val;
}

AgxVector *agx_vector_new_values(double *array, int size) {
    AgxVector *vec = agx_vector_new(size);
    if (vec == NULL) {
        fprintf(stderr, "vec cannot be allocated\n");
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        vec->p_r_nums[i] = array[i];
    }
    return vec;
}

void agx_vector_input_function(AgxVector *vec, void (*function)(double *)) {
    for (int i = 0; i < vec->size; i++) {
        function(&(vec->p_r_nums[i]));
    }
}

void agx_sin(double *val) {
    *val = sin(*val);
}

void agx_vector_sin(AgxVector *vec) {
    agx_vector_input_function(vec, agx_sin);
}

int agx_vector_isexist(AgxVector *vec, int idx1, int idx2, double val) {
    int res = 0;
    for (int i = idx1; i <= idx2; i++) {
        if (val == vec->p_r_nums[i]) {
            res = 1;
        }
    }
    return res;
}

int agx_vector_sort(AgxVector *vec) {
    AgxVector *temp;
    AgxVector *vec_new = agx_vector_new_constant(vec->size, 0.);
    if (vec_new == NULL) {
        fprintf(stderr, "vec_new cannot be allocated\n");
        return -1;
    }
    double val, min;
    int n;
    vec_new->p_r_nums[0] = agx_vector_min(vec);
    for (int i = 1; i < vec->size; i++) {
        val = vec_new->p_r_nums[i-1];
        temp = agx_vector_new(vec->size - i);
        if (temp == NULL) {
            fprintf(stderr, "temp cannot be allocated\n");
            return -1;
        }
        n = 0;
        for (int j = 0; j < vec->size; j++) {
            if (val < vec->p_r_nums[j] && agx_vector_isexist(vec_new, 0, i - 1, vec->p_r_nums[j]) == 0) {
                temp->p_r_nums[n] = vec->p_r_nums[j];
                n++;
            }
        }
        min = agx_vector_min(temp);
        vec_new->p_r_nums[i] = min;
        agx_vector_delete(&temp);
    }
    agx_vector_copy_elements(vec_new, vec);
    agx_vector_delete(&vec_new);
    return 0;
}