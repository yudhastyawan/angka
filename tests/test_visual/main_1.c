#include "angka.h"

int main() {
    int size = 100;
    AgxVector *vecx = agx_vector_new_linspace(0., 10., size);
    AgxVector *vecy = agx_vector_new_random(size, -10., 10.);

    AgvFigure *fig = agv_subplots(2,2);
    agv_plot(agv_set_canvas(fig, 0), vecx, vecy);
    agv_scatter(agv_set_canvas(fig, 0), vecx, vecy);
    agv_set_color_alpha(agv_set_canvas(fig, 0), 0, 255, 100, 127, 0.7);
    agv_set_color_alpha(agv_set_canvas(fig, 0), 1, 0, 0, 255, 0.4);
    agv_set_color_alpha_line(agv_set_canvas(fig, 0), 1, 255, 0, 0, 0.4);
    agv_set_radius(agv_set_canvas(fig, 0), 1, 10);

    agv_plot(agv_set_canvas(fig, 1), vecx, vecy);
    agv_set_color_alpha(agv_set_canvas(fig, 1), 0, 93, 241, 93, 1.);
    agv_set_grid(agv_set_canvas(fig, 1), TRUE);

    agv_plot(agv_set_canvas(fig, 2), vecx, vecy);
    agv_plot(agv_set_canvas(fig, 3), vecx, vecy);
    agv_set_linewidth(agv_set_canvas(fig, 3), 0, 20);
    for (int i = 0; i < fig->size; i++) {
        agv_xlim(agv_set_canvas(fig, i), 0., 10.);
        agv_ylim(agv_set_canvas(fig, i), -10., 10.);
    }

    agv_show(fig);
    agv_figure_delete(&fig);

    agx_vector_delete(&vecx);
    agx_vector_delete(&vecy);
    return 0;
}