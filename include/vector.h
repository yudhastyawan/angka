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

/**
 * @brief creating vector data type in this library
 * @details after this struct is created, we need to delete 
 *          unused using @ref agx_vector_delete.
 *          Usually we call this struct using its typedef @ref AgxVector
 **/
typedef struct s_vector {
    /// array of vector
    double *p_r_nums;
    /// length of array
    int size;
} AgxVector;

/**
 * @brief create an empty vector with a certain size
 * @note we can use @ref agx_vector_new_zero to make sure that
 *       the initial value for each element is zero.
 **/
AgxVector *agx_vector_new(int size);

/**
 * @brief set value in a certain element of vector
 * @param vec overwrite the existing vector
 * @param index the index of vector
 * @param val the value for that index
 **/
void *agx_vector_set_item(AgxVector *vec, int index, double val);

/**
 * @brief get value in a certain element of vector
 * @return the value of that index in vector array
 * */
double agx_vector_get_item(AgxVector *vec, int index);

/**
 * @brief convert vector to string
 * @details it is used for saving the string before put in the print function
 * @note we need to delete this manually using @ref agx_data_delete because it remains in memory
 * */
p_vectorString_t agx_vector_to_string(AgxVector *vec, int islong);

/**
 * @brief delete vector
 * */
void agx_vector_delete(AgxVector *vec);

/**
 * @brief create a vector with random values
 * */
AgxVector *agx_vector_new_random(int size, double min, double max);

/**
 * @brief print vector in the console
 * @details it is using @ref agx_vector_to_string to create a string vector and
 *          this function has automatically delete the return of @ref agx_vector_to_string
 * @param islong BOOLEAN for deciding that it is partial (0) or full vector (1) that need to be printed
 * */
void *agx_vector_print(AgxVector *vec, int islong);

/**
 * @brief append vector with a value in the end of vector array
 **/
void *agx_vector_append_value(AgxVector *vec, double val);

/**
 * @brief append vector with another vector and overwriting
 * */
void *agx_vector_append_vector(AgxVector *vec_target, AgxVector *vec_another);

/**
 * @brief print the partial of vector
 * @details it is based on @ref agx_vector_print with islong = 0
 * */
void *agx_vector_print_partial(AgxVector *vec);

/**
 * @brief print the full of vector
 * @details it is based on @ref agx_vector_print with islong = 1
 * */
void *agx_vector_print_full(AgxVector *vec);

/**
 * @brief adding all elements of vector by a value
 * */
void *agx_vector_add_by_value(AgxVector *vec, double val);

/**
 * @brief substracting all elements of vector by a value
 * */
void *agx_vector_substract_by_value(AgxVector *vec, double val);

/**
 * @brief multiplying all elements of vector by a value
 * */
void *agx_vector_multiply_by_value(AgxVector *vec, double val);

/**
 * @brief dividing all elements of vector by a value
 * */
void *agx_vector_divide_by_value(AgxVector *vec, double val);

/**
 * @brief changing all elements of vector by a value
 * */
void *agx_vector_change_elements_by_value(AgxVector *vec, double val);

/**
 * @brief create @ref agx_vector_new with a constant value
 * */
AgxVector *agx_vector_new_constant(int size, double val);

/**
 * @brief create @ref agx_vector_new by using the size of another vector
 * */
AgxVector *agx_vector_new_duplicate_size(AgxVector *vec);

/**
 * @brief copy all elements of a vector to a target vector
 * @note both vectors must be the same size
 * */
void *agx_vector_copy_elements(AgxVector *src, AgxVector *target);

/**
 * @brief create @ref agx_vector_new by copying another vector
 * */
AgxVector *agx_vector_new_copy(AgxVector *vec);

/**
 * @brief create @ref agx_vector_new_constant with zero value
 * */
AgxVector *agx_vector_new_zero(int size);

/**
 * @brief create a new range vector by using the size value
 * */
AgxVector *agx_vector_new_linspace(double min, double max, int size);

/**
 * @brief create a new range vector using the interval value
 * @param step the interval value
 * @note the input is integer and the output is a double array
 * */
AgxVector *agx_vector_new_arange(int min, int step, int max);

/**
 * @brief create a new range vector using the interval value
 * @param step the interval value
 * @note the input is double and the output is a double array
 * */
AgxVector *agx_vector_new_arange_double(double min, double step, double max);

/**
 * @brief looking for the minimum value of vector
 * */
double agx_vector_min(AgxVector *vec);

/**
 * @brief looking for the maximum value of vector
 * */
double agx_vector_max(AgxVector *vec);

/**
 * @brief create a vector using the varadic values
 * @note the size and number of values must be the same
 * */
AgxVector *agx_vector_new_values(int size, ... );

/**
 * @brief change each element of vector based on a certain function
 * @note the input of function should be only one and double pointer
 * */
void *agx_vector_input_function(AgxVector *vec, void (*function)(double *));

/**
 * @brief the sinus of each element of the vector
 * */
void *agx_vector_sin(AgxVector *vec);

/**
 * @brief the double sinus
 * */
void agx_sin(double *val);

/**
 * @brief checking a value is exist on the vector in a certain indexes range
 * @note index i where idx1 <= i <= idx2
 * */
int agx_vector_isexist(AgxVector *vec, int idx1, int idx2, double val);

/**
 * @brief sorting the elements of vector from minimum to maximum
 * */
void *agx_vector_sort(AgxVector *vec);

#ifdef __cplusplus
}
#endif

#endif