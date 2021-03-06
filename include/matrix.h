/**
 * \file matrix.h
 * @brief the library for matrix data manipulation
 * 
 * */

#ifndef __MATRIX_H
#define __MATRIX_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief matrix string typedef
 * @details it is used for indentifying that this typedef need to be delete in memory before quit a program.
 *          Deleting this type can use @ref agx_data_delete in @ref standard.h.
 **/
typedef char * p_matrixString_t;

/**
 * @brief creating matrix data type in this library
 * @details after this struct is created, we need to delete 
 *          unused using @ref agx_matrix_delete.
 *          Usually we call this struct using its typedef @ref AgxMatrix
 **/
typedef struct s_matrix {
    /// array of the matrix
    double *p_r_nums;
    /// shape of the matrix (m x n)
    int r_shape[2];
    /// size of the matrix
    int size;
} AgxMatrix;

/**
 * @brief create an empty matrix with a certain row and column
 * @note we can use @ref agx_matrix_new_zero to make sure that
 *       the initial value for each element is zero.
 * @return NULL if matrix cannot be allocated.
 **/
AgxMatrix *agx_matrix_new(int row, int column);

/**
 * @brief delete matrix
 * */
void agx_matrix_delete(AgxMatrix **mat);

/**
 * @brief change all elements of matrix by a value
 * @return 0 if success, -1 if error.
 * */
int agx_matrix_change_elements_by_value(AgxMatrix *mat, double val);

/**
 * @brief create a new matrix with a constant value
 * @return AgxMatrix, NULL if error.
 * */
AgxMatrix *agx_matrix_new_constant(int row, int column, double val);

/**
 * @brief create a new matrix with some random values
 * @return AgxMatrix, NULL if error.
 * */
AgxMatrix *agx_matrix_new_random(int row, int column, double min, double max);

/**
 * @brief create a new matrix from C array
 * @param dim1 equals to row number
 * @param dim2 equals to column number
 * @return AgxMatrix, NULL if error.
 * @note this function is prioritized to be a Python wrapping
 * */
AgxMatrix *agx_matrix_new_from_array(double *ndarray_in, int dim1, int dim2);

/**
 * @brief passing the array reference to ndarray_out
 * @warning it is still not recommended to use it, especially after wrapping to Python
 *          due to being not able to deal with the data malloc in ndarray_out
 * */
void agx_matrix_to_array(AgxMatrix *mat, double **ndarray_out, int *dim1, int *dim2);

/**
 * @brief change row and col values to index of array matrix
 * */
int agx_matrix_row_col_to_index(AgxMatrix *mat, int row, int col);

/**
 * @brief set a value in a corresponding row and column 
 * @return 0 if success, -1 if error.
 * */
int agx_matrix_set_item(AgxMatrix *mat, int row, int col, double val);

/**
 * @brief get the value from matrix based on row and column
 * @return 0 if success, -1 if error.
 * */
int agx_matrix_get_item(AgxMatrix *mat, int row, int col, double *output);

/**
 * @brief change a matrix to matrix string
 * @return NULL if error.
 * @note you need to delete this manually after using it.
 * */
p_matrixString_t agx_matrix_to_string(AgxMatrix *mat, int islong);

/**
 * @brief print a matrix in the console with islong parameter
 * @return 0 if success, -1 if error.
 * */
int agx_matrix_print(AgxMatrix *mat, int islong);

/**
 * @brief print a matrix in a partial form (islong = 0)
 * @return 0 if success, -1 if error.
 * */
int agx_matrix_print_partial(AgxMatrix *mat);

/**
 * @brief print a matrix in a full form (islong = 1)
 * @return 0 if success, -1 if error.
 * */
int agx_matrix_print_full(AgxMatrix *mat);

/**
 * @brief adding all elements of matrix by a value
 * @return 0 if success, -1 if error.
 * */
int agx_matrix_add_by_value(AgxMatrix *mat, double val);

/**
 * @brief substracting all elements of matrix by a value
 * @return 0 if success, -1 if error.
 * */
int agx_matrix_substract_by_value(AgxMatrix *mat, double val);

/**
 * @brief multiplying all elements of matrix by a value
 * @return 0 if success, -1 if error.
 * */
int agx_matrix_multiply_by_value(AgxMatrix *mat, double val);

/**
 * @brief dividing all elements of matrix by a value
 * @return 0 if success, -1 if error.
 * */
int agx_matrix_divide_by_value(AgxMatrix *mat, double val);

/**
 * @brief create a new matrix based on the row of col values on another matrix
 * @return AgxMatrix, NULL if error.
 * */
AgxMatrix *agx_matrix_new_duplicate_size(AgxMatrix *mat);

/**
 * @brief copy all elements of the vector to the target vector
 * @return 0 if success, -1 if error.
 * @note the col and row values must be the same
 * */
int agx_matrix_copy_elements(AgxMatrix *src, AgxMatrix *target);

/**
 * @brief copy shape the vector to the target vector
 * @return 0 if success, -1 if error.
 * @note both matrix must have the same size
 * */
int agx_matrix_copy_shape(AgxMatrix *src, AgxMatrix *target);

/**
 * @brief transpose the matrix
 * @return 0 if success, -1 if error.
 * */
int agx_matrix_transpose(AgxMatrix *mat);

/**
 * @brief copy the matrix
 * @return AgxMatrix, NULL if error.
 * */
AgxMatrix *agx_matrix_new_copy(AgxMatrix *mat);

/**
 * @brief create a new matrix based on the vector
 * @return AgxMatrix, NULL if error.
 * @note it will create a shape (1 x n)
 * */
AgxMatrix *agx_matrix_new_from_vector(AgxVector *vec);

/**
 * @brief create a new identity matrix (m x m)
 * @return AgxMatrix, NULL if error.
 * */
AgxMatrix *agx_matrix_new_identity(int size);

/**
 * @brief create a new zero matrix
 * @return AgxMatrix, NULL if error.
 * */
AgxMatrix *agx_matrix_new_zero(int row, int col);

/**
 * @brief matrix multiplication and stored in the new matrix
 * @return AgxMatrix, NULL if error.
 * */
AgxMatrix *agx_matrix_new_multiplication(AgxMatrix *mat1, AgxMatrix *mat2);

/**
 * @brief create a new vector from the matrix
 * @return AgxVector, NULL if error.
 * */
AgxVector *agx_vector_new_from_matrix(AgxMatrix *mat);

/**
 * @brief create a new matrix based on a certain column values
 * @return AgxMatrix, NULL if error.
 * */
AgxMatrix *agx_matrix_new_extract_column(AgxMatrix *mat, int col);

/**
 * @brief create a new matrix based on a certain row values
 * @return AgxMatrix, NULL if error.
 * */
AgxMatrix *agx_matrix_new_extract_row(AgxMatrix *mat, int row);

/**
 * @brief create a new matrix based on a certain row and column range
 * @return AgxMatrix, NULL if error.
 * */
AgxMatrix *agx_matrix_new_extract_row_col(AgxMatrix *mat, int row1, int row2, int col1, int col2);

/**
 * @brief look for a minimum value of the matrix
 * */
double agx_matrix_min(AgxMatrix *mat);

/**
 * @brief look for a maximum value of the matrix
 * */
double agx_matrix_max(AgxMatrix *mat);

#ifdef __cplusplus
}
#endif

#endif