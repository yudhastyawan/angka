#include "angka.h"

/**
 * @brief Create a matrix, print, and delete it 
 * @details @ref agx_matrix_new_random with row = 6, col = 10 from -8. to 5.
 *          print all elements using @ref agx_matrix_print_full
 *          delete the memory, including an array inside matrix
 *          using @ref agx_matrix_delete.
 * @warning every @ref AgxMatrix that has been created, need to
 *          delete eventough you still need it until the end of
 *          program. This will make sure that @ref AgxMatrix has
 *          been destroy in the computer. That is bad thing if
 *          we ignore this and let the operating system handle it
 *          for us.
 **/
int main() {
    AgxMatrix *vec = agx_matrix_new_random(6, 10, -8., 5.);
    agx_matrix_print_full(vec);
    agx_matrix_print_partial(vec);
    agx_matrix_delete(&vec);
    return 0;
}