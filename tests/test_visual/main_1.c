#include "angka.h"
#include "angkavisual.h"

int main() {
    int size = 100;
    AgxVector *vecx = agx_vector_new_linspace(0., 10., size);
    AgxVector *vecy = agx_vector_new_random(size, -10., 10.);
    
    agx_vector_print_partial(vecx);
    agx_vector_print_partial(vecy);

    agv_plot(vecx, vecy);

    agx_vector_delete(vecx);
    agx_vector_delete(vecy);
    return 0;
}