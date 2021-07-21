#include "angka.h"

int main() {
    AgxVector *vecx = agx_vector_new_linspace(1., 15., 30);
    AgxVector *vecy = agx_vector_new_linspace(20., 30., 30);
    
    agx_vector_print_full(vecx);
    agx_vector_print_full(vecy);

    agx_vector_delete(vecx);
    agx_vector_delete(vecy);
    return 0;
}