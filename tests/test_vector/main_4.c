#include "angka.h"

int main() {
    AgxVector *vec = agx_vector_new_random(8, -10., 10.);
    agx_vector_print_full(vec);
    agx_vector_sort(vec);
    agx_vector_print_full(vec);
    agx_vector_delete(vec);
    return 0;
}