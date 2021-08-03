/**
 * \file grid.h
 * @brief the library for grid data manipulation
 * 
 * */

#ifndef __GRID_H
#define __GRID_H

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief grid structure data
 * */
typedef struct s_grid {
    /// r_shape in malloc 1d data
    int *r_shape;
    /// p_r_nums in malloc 1d data
    double *p_r_nums;

    /// the length of malloc p_r_nums
    int size;

    /// the length of r_shape
    int ndim;
} AgxGrid;


/**
 * @brief create a grid data in malloc
 * @warning need to be deleted before closing the program or after data is unused using @ref agx_grid_delete
 * @param shape array input dimensional values beginning with {x1, ..., xn}
 * @param ndim the length of dimensional data N {x1, ..., xn}
 * @note AgxGrid = NULL if grid cannot be allocated.
 * */
AgxGrid *agx_grid_new(int *shape, int ndim);

/**
 * @brief delete @ref agx_grid_new
 * */
void agx_grid_delete(AgxGrid **grid);

/**
 * @brief convert dimensional indexes to 1d index
 * @param indexes input dimensional indexes {x1, ..., xn}
 * @param ndim length of dimensional input N
 * @return idx if idx < size of array, otherwise is -1
 * */
int agx_grid_idim2index(AgxGrid *grid, int *indexes, int ndim);

/**
 * @brief convert 1d index to dimensional indexes
 * @return malloc shape that need to be deleted using free()
 * @note return NULL if shape cannot be allocated
 * */
int *agx_grid_index2dim(AgxGrid *grid, int index);

/**
 * @brief using @ref agx_grid_index2dim only for a certain dimensional index.
 * @note the return in @ref agx_grid_index2dim has been deleted in the function.
 * @return index in n-dimensional index.
 * @note return -1 if error.
 * */
int agx_grid_index2idim(AgxGrid *grid, int idim, int index);

#ifdef __cplusplus
}
#endif

#endif