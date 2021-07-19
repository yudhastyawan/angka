#include "init.h"
#include "standard.h"
#include "vector.h"
#include <malloc.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

AgxVector *agx_vector_new(int size) {
    AgxVector *vec;
    vec = (AgxVector *)malloc(sizeof(AgxVector));
    vec->p_r_nums = (double *)malloc((size)*sizeof(double));
    vec->size = size;
    return vec;
}

void *agx_vector_set_item(AgxVector *vec, int index, double val) {
    if(index < vec->size) {
        vec->p_r_nums[index] = val;
    } else {
        return NULL;
    }
}

double agx_vector_get_item(AgxVector *vec, int index) {
    if (index < vec->size) {
        return vec->p_r_nums[index];
    }
}

p_vectorString_t agx_vector_to_string(AgxVector *vec, int islong) {
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
    temp_length = snprintf(0,0,"%d",vec->size)+1;
    char *temp_string = malloc(temp_length);
    snprintf(temp_string, temp_length, "%d", vec->size);
    strcpy(vec_string, temp_string);
    free(temp_string);
    strcat(vec_string, " [");
    if (islong == 1 || vec->size <= 5) {
        for (i = 0; i < vec->size; i++) {
            temp_length = snprintf(0,0,"%f",vec->p_r_nums[i]);
            char *temp_string = malloc(temp_length);
            snprintf(temp_string, temp_length, "%f", vec->p_r_nums[i]);
            strcat(vec_string, temp_string);
            if (i < (vec->size-1)) {
                strcat(vec_string, ", ");
            }
            free(temp_string);
        }
    } else {
        for (i = 0; i < vec->size; i++) {
            if (i < 4) {
                temp_length = snprintf(0,0,"%f",vec->p_r_nums[i]);
                char *temp_string = malloc(temp_length);
                snprintf(temp_string, temp_length, "%f", vec->p_r_nums[i]);
                strcat(vec_string, temp_string);
                if (i < 3) {
                    strcat(vec_string, ", ");
                } else {
                    strcat(vec_string, ",..., ");
                }
                free(temp_string);
            }
            if (i == (vec->size-1)) {
                temp_length = snprintf(0,0,"%f",vec->p_r_nums[i]);
                char *temp_string = malloc(temp_length);
                snprintf(temp_string, temp_length, "%f", vec->p_r_nums[i]);
                strcat(vec_string, temp_string);
                free(temp_string);
            }
        }
    }
    strcat(vec_string, "]\n");
    return vec_string;
}

void agx_vector_delete(AgxVector *vec) {
    free(vec->p_r_nums);
    free(vec);
}

AgxVector *agx_vector_new_random(int size, double min, double max) {
    AgxVector *vec = agx_vector_new(size);
    double val;
    for(int i = 0; i < vec->size; i++) {
        val = agx_random(min, max);
        agx_vector_set_item(vec, i, val);
    }
    return vec;
}

void *agx_vector_print(AgxVector *vec, int islong) {
    p_vectorString_t vec_str = agx_vector_to_string(vec, islong);
    printf("%s", vec_str);
    agx_data_delete(vec_str);
}

void *agx_vector_append_value(AgxVector *vec, double val) {
    vec->p_r_nums = (double *)realloc(vec->p_r_nums, (vec->size+1)*sizeof(double));
    vec->p_r_nums[vec->size] = val;
    vec->size += 1;
}

void *agx_vector_append_vector(AgxVector *vec_target, AgxVector *vec_another) {
    vec_target->p_r_nums = (double *)
        realloc(vec_target->p_r_nums, (vec_target->size+vec_another->size)
            *sizeof(double));
    for(int i = vec_target->size; i < (vec_target->size + vec_another->size); i++){
        vec_target->p_r_nums[i] = vec_another->p_r_nums[i-vec_target->size];
    }
    vec_target->size += vec_another->size;
}

void *agx_vector_print_partial(AgxVector *vec){
    agx_vector_print(vec, 0);
}

void *agx_vector_print_full(AgxVector *vec){
    agx_vector_print(vec, 1);
}

void *agx_vector_add_by_value(AgxVector *vec, double val) {
    for (int i = 0; i < vec->size; i++) {
        vec->p_r_nums[i] += val;
    }
}

void *agx_vector_substract_by_value(AgxVector *vec, double val) {
    for (int i = 0; i < vec->size; i++) {
        vec->p_r_nums[i] -= val;
    }
}

void *agx_vector_multiply_by_value(AgxVector *vec, double val) {
    for (int i = 0; i < vec->size; i++) {
        vec->p_r_nums[i] *= val;
    }
}

void *agx_vector_devide_by_value(AgxVector *vec, double val) {
    for (int i = 0; i < vec->size; i++) {
        vec->p_r_nums[i] /= val;
    }
}

void *agx_vector_change_elements_by_value(AgxVector *vec, double val) {
    for (int i = 0; i < vec->size; i++) {
        vec->p_r_nums[i] = val;
    }
}

AgxVector *agx_vector_new_constant(int size, double val) {
    AgxVector *vec = agx_vector_new(size);
    agx_vector_change_elements_by_value(vec, val);
    return vec;
}

AgxVector *agx_vector_new_duplicate_size(AgxVector *vec) {
    AgxVector *vec_new = agx_vector_new(vec->size);
    return vec_new;
}

void *agx_vector_copy_elements(AgxVector *src, AgxVector *target) {
    if (src->size == target->size) {
        for (int i = 0; i < target->size; i++) {
            target->p_r_nums[i] = src->p_r_nums[i];
        }
    }
}

AgxVector *agx_vector_new_copy(AgxVector *vec) {
    AgxVector *vec_new = agx_vector_new_duplicate_size(vec);
    agx_vector_copy_elements(vec, vec_new);
    return vec_new;
}

AgxVector *agx_vector_new_zero(int size) {
    return agx_vector_new_constant(size, 0.);
}

AgxVector *agx_vector_new_linspace(double min, double max, int size) {
    AgxVector *vec = agx_vector_new(size);
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

AgxVector *agx_vector_new_values(int size, ... ) {
    AgxVector *vec = agx_vector_new(size);
    va_list args;
    va_start(args, size);
    for (int i = 0; i < size; i++) {
        vec->p_r_nums[i] = va_arg(args, double);
    }
    va_end(args);
    return vec;
}

void *agx_vector_input_function(AgxVector *vec, void (*function)(double *)) {
    for (int i = 0; i < vec->size; i++) {
        function(&(vec->p_r_nums[i]));
    }
}

void agx_sin(double *val) {
    *val = sin(*val);
}

void *agx_vector_sin(AgxVector *vec) {
    agx_vector_input_function(vec, agx_sin);
}