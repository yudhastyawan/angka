#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

AgxGrid *agx_grid_new(int ndim, ...) {
    AgxGrid *grid = (AgxGrid *)malloc(sizeof(AgxGrid));
    grid->r_shape = (int *)malloc(ndim*sizeof(int));
    grid->ndim = ndim;
    grid->size = 1;

    va_list args;
    va_start(args,ndim);
    for(int i = 0; i < ndim; i++){
        int idim = va_arg(args, int);
        grid->r_shape[i] = idim;
        grid->size *= idim;
    }
    va_end(args);

    grid->p_r_nums = (double *)malloc(grid->size*sizeof(double));

    return grid;
}

void agx_grid_delete(AgxGrid *grid) {
    free(grid->p_r_nums);
    free(grid->r_shape);
    free(grid);
}

int agx_grid_idim2index(AgxGrid *grid, int ndim, ...) {
    int idx = 0;
    va_list args;
    va_start(args, ndim);

    for (int i = 0; i < ndim; i++){
        int val = va_arg(args, int);
        int mul = 1;
        for (int j = 0; j < i; j++) {
            mul *= grid->r_shape[j];
        }
        idx += val * mul;
    }

    va_end(args);
    return idx;
}

int *agx_grid_index2dim(AgxGrid *grid, int index) {
    int mod;
    int *ishape = (int *)malloc(grid->ndim*sizeof(int));
    for (int i = grid->ndim - 1; i >= 0; i--) {
        mod = 1;
        for (int j = 0; j < i; j++) {
            mod *= grid->r_shape[j];
        }
        ishape[i] = index / mod;
        index = index % mod;
    }
    return ishape;
}

int agx_grid_index2idim(AgxGrid *grid, int idim, int index) {
    int idx;
    int *ishape = agx_grid_index2dim(grid, index);
    idx = ishape[idim];
    free(ishape);
    return idx;
}