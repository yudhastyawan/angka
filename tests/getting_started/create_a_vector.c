#include "angka.h"

/**
 * @brief Create a vector, print, and delete it 
 * @details @ref agx_vector_new_random with size = 10 from -8. to 5.
 *          print all elements using @ref agx_vector_print_full
 *          delete the memory, including an array inside vector
 *          using @ref agx_vector_delete.
 * @warning every @ref AgxVector that has been created, need to
 *          delete eventough you still need it until the end of
 *          program. This will make sure that @ref AgxVector has
 *          been destroy in the computer. That is bad thing if
 *          we ignore this and let the operating system handle it
 *          for us.
 **/
int main() {
    //! [create a vector]
    AgxVector *vec = agx_vector_new_random(10, -8., 5.);
    //! [create a vector]
    //! [print a vector]
    agx_vector_print_full(vec);
    //! [print a vector]
    //! [print a vector in a short mode]
    agx_vector_print_partial(vec);
    //! [print a vector in a short mode]
    //! [delete a vector]
    agx_vector_delete(vec);
    //! [delete a vector]
    return 0;
}