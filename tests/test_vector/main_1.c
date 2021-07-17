#include "angka.h"

int main() {
    AgxVector *vec = agx_vector_new_constant(10, 4.);
    agx_vector_print_partial(vec);

    agx_vector_add_by_value(vec, 2.);
    agx_vector_print_full(vec);

    agx_vector_multiply_by_value(vec, 2.);
    agx_vector_print_partial(vec);

    agx_vector_append_value(vec, 10.);
    agx_vector_print_partial(vec);

    AgxVector *vec_another = agx_vector_new_copy(vec);
    agx_vector_change_elements_by_value(vec_another, 1.5);
    agx_vector_append_vector(vec, vec_another);
    agx_vector_print_partial(vec);

    AgxVector *vec_zero = agx_vector_new_zero(4);
    agx_vector_set_item(vec_zero, 1, 4.);
    agx_vector_print_partial(vec_zero);

    agx_vector_delete(vec);
    agx_vector_delete(vec_another);
    agx_vector_delete(vec_zero);
    return 0;
}