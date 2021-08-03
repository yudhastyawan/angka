#include "angka.h"

int main() {
    double array[] = {1., 4., 7., 8., 10.};
    AgxVector *vec = agx_vector_new_values(array, 5);
    agx_vector_print_full(vec);
    agx_vector_delete(&vec);
    vec = agx_vector_new_arange(0, 2, 15);
    agx_vector_print_full(vec);
    agx_vector_delete(&vec);
    agx_print_values("\n", "nice to see you\n", "dcfs", 5, 'a', 2.0, "yes");
    agx_print_values_space("dcfs", 5, 'a', 2.0, "yes");
    agx_print_values_new_line("dcfs", 5, 'a', 2.0, "yes");
    return 0;
}