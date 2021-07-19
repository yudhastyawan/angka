#include "angka.h"
#include "angkavisual.h"
#include <math.h>

int main() {
    int size = 100;
    AgxVector *vecx = agx_vector_new_linspace(0., 10., size);
    AgxVector *vecy = agx_vector_new_random(size, -10., 10.);

    AgvFigure *fig = agv_subplots(1,2);
    agv_plot(agv_set_canvas(fig, 0), vecx, vecy);
    agv_scatter(agv_set_canvas(fig, 0), vecx, vecy);
    agv_set_color_alpha(agv_set_canvas(fig, 0), 0, 255, 100, 127, 0.7);
    agv_set_color_alpha(agv_set_canvas(fig, 0), 1, 0, 0, 255, 0.4);
    agv_set_color_alpha_line_scatter(agv_set_canvas(fig, 0), 1, 255, 0, 0, 0.4);
    agv_set_radius(agv_set_canvas(fig, 0), 1, 10);

    AgxVector *vecx2 = agx_vector_new_linspace(0., 4*M_PI, size);
    AgxVector *vecy2 = agx_vector_new_copy(vecx2);
    agx_vector_sin(vecy2);

    agv_scatter(agv_set_canvas(fig, 1), vecx2, vecy2);
    agv_set_color_alpha(agv_set_canvas(fig, 1), 0, 0, 255, 0, 0.8);
    agv_set_color_alpha_line_scatter(agv_set_canvas(fig, 1), 0, 255, 100, 127, 0.7);
    agv_set_radius(agv_set_canvas(fig, 1), 0, 10);    

    agv_show(fig);
    agv_figure_delete(fig);
    agx_vector_delete(vecx);
    agx_vector_delete(vecy);
    agx_vector_delete(vecx2);
    agx_vector_delete(vecy2);
    return 0;
}