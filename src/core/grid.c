#include "grid.h"
#include <stdio.h>
#include <stdlib.h>

AgxGrid *agx_grid_new(int *shape, int ndim) {
    AgxGrid *grid = malloc(sizeof(AgxGrid));
    if (grid == NULL) {
        fprintf(stderr, "grid cannot be allocated\n");
        return grid;
    }

    if (ndim == 0) {
        fprintf(stderr, "dimensional size (ndim) could not be zero, set at least 1 and" 
                        "make sure that shape array length (shape) equals to ndim\n");
        grid = NULL;
        return grid;
    }

    grid->r_shape = malloc(ndim*sizeof(int));
    if (grid->r_shape == NULL) {
        fprintf(stderr, "grid->r_shape cannot be allocated\n");
        grid = NULL;
        return grid;
    }
    grid->ndim = ndim;
    grid->size = 1;

    for(int i = 0; i < ndim; i++){
        grid->r_shape[i] = shape[i];
        grid->size *= shape[i];
    }

    grid->p_r_nums = malloc(grid->size*sizeof(double));
    if (grid->p_r_nums == NULL) {
        fprintf(stderr, "grid->p_r_nums cannot be allocated\n");
        grid = NULL;
        return grid;
    }

    return grid;
}

void agx_grid_delete(AgxGrid **grid) {
    if (*grid == NULL) {
        return;
    }
    free((*grid)->p_r_nums);
    (*grid)->p_r_nums = NULL;
    free((*grid)->r_shape);
    (*grid)->r_shape = NULL;
    free(*grid);
    *grid = NULL;
}

int agx_grid_idim2index(AgxGrid *grid, int *indexes, int ndim) {
    int idx = 0;

    for (int i = 0; i < ndim; i++){
        int mul = 1;
        for (int j = 0; j < i; j++) {
            mul *= grid->r_shape[j];
        }
        idx += indexes[i] * mul;
    }

    if (idx >= grid->size) {
        fprintf(stderr, "the index exceed the size of array\n");
        return -1;
    }

    return idx;
}

int *agx_grid_index2dim(AgxGrid *grid, int index) {
    if (index < 0 || index >= grid->size) {
        fprintf(stderr, "index has to positive integer\n");
        return NULL;
    }
    int mod;
    int *ishape = malloc(grid->ndim*sizeof(int));
    if (ishape == NULL) {
        fprintf(stderr, "ishape cannot be allocated\n");
        return NULL;
    }
    for (int i = grid->ndim - 1; i >= 0; i--) {
        mod = 1;
        for (int j = 0; j < i; j++) {
            mod *= grid->r_shape[j];
        }
        ishape[i] = index / mod;
        if (ishape[i] >= grid->r_shape[i]) {
            fprintf(stderr, "value of the index exceeds the shape of grid\n");
            return NULL;
        }
        index = index % mod;
    }
    return ishape;
}

int agx_grid_index2idim(AgxGrid *grid, int idim, int index) {
    int idx;
    if (index < 0 || index >= grid->size || idim >= grid->ndim) {
        fprintf(stderr, "index has to positive integer less than the size of array or idim has to less than dimensional grid\n");
        return -1;
    }
    int *ishape = agx_grid_index2dim(grid, index);
    if (ishape == NULL) {
        fprintf(stderr, "ishape cannot be allocated\n");
        return -1;
    }
    idx = ishape[idim];
    free(ishape);
    ishape = NULL;
    if (idx >= grid->r_shape[idim]) {
        fprintf(stderr, "idx exceeds the size of i-dimension\n");
        return -1;
    }
    return idx;
}