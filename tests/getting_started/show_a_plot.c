#include "angka.h"
#include "angkavisual.h"

int main() {
    int size = 100;
    AgxVector *vecx = agx_vector_new_linspace(0., 15., size);
    AgxVector *vecy = agx_vector_new_random(size, -10, 10.);

    AgvFigure *fig = agv_subplots(1,1);
    agv_plot(agv_set_canvas(fig, 0), vecx, vecy);
    agv_show(fig);

    agv_figure_delete(fig);
    agx_vector_delete(vecx);
    agx_vector_delete(vecy);
    return 0;
}