/**
 * \file vector.h
 * @brief the library for vector data manipulation
 * 
 * */

#ifndef __VECTOR_H
#define __VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief vector string typedef
 * @details it is used for indentifying that this typedef need to be delete in memory before quit a program.
 *          Deleting this type can use @ref agx_data_delete in @ref standard.h.
 **/
typedef char * p_vectorString_t;

typedef struct s_vector {
    double *p_r_nums;
    int size;
} AgxVector;

AgxVector *agx_vector_new(int size);
void *agx_vector_set_item(AgxVector *vec, int index, double val);
double agx_vector_get_item(AgxVector *vec, int index);
p_vectorString_t agx_vector_to_string(AgxVector *vec, int islong);
void agx_vector_delete(AgxVector *vec);
AgxVector *agx_vector_new_random(int size, double min, double max);
void *agx_vector_print(AgxVector *vec, int islong);
void *agx_vector_append_value(AgxVector *vec, double val);
void *agx_vector_append_vector(AgxVector *vec_target, AgxVector *vec_another);
void *agx_vector_print_partial(AgxVector *vec);
void *agx_vector_print_full(AgxVector *vec);
void *agx_vector_add_by_value(AgxVector *vec, double val);
void *agx_vector_substract_by_value(AgxVector *vec, double val);
void *agx_vector_multiply_by_value(AgxVector *vec, double val);
void *agx_vector_devide_by_value(AgxVector *vec, double val);
void *agx_vector_change_elements_by_value(AgxVector *vec, double val);
AgxVector *agx_vector_new_constant(int size, double val);
AgxVector *agx_vector_new_duplicate_size(AgxVector *vec);
void *agx_vector_copy_elements(AgxVector *src, AgxVector *target);
AgxVector *agx_vector_new_copy(AgxVector *vec);
AgxVector *agx_vector_new_zero(int size);
AgxVector *agx_vector_new_linspace(double min, double max, int size);
AgxVector *agx_vector_new_arange(int min, int step, int max);
AgxVector *agx_vector_new_arange_double(double min, double step, double max);
double agx_vector_min(AgxVector *vec);
double agx_vector_max(AgxVector *vec);
AgxVector *agx_vector_new_values(int size, ... );
void *agx_vector_input_function(AgxVector *vec, void (*function)(double *));
void *agx_vector_sin(AgxVector *vec);
void agx_sin(double *val);
int agx_vector_isexist(AgxVector *vec, int idx1, int idx2, double val);
void *agx_vector_sort(AgxVector *vec);

#ifdef __cplusplus
}
#endif

#endif