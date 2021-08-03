#include "angka.h"

int main() {
    AgxMatrix *mat = agx_matrix_new_random(57, 35, -10, 10);
    agx_matrix_print_partial(mat);
    AgvFigure *fig = agv_subplots(1,1);
    agv_imshow(agv_set_canvas(fig, 0), mat);
    AgxColor *clr = agv_color_pallete_canvas_set_size(agv_set_canvas(fig, 0), 0, 3);
    agv_color_pallete_set(clr, 0, 175, 19, 132, 1., -10.);
    agv_color_pallete_set(clr, 1, 250, 157, 20, 1., -3.);
    // agv_color_pallete_set(clr, 2, 60, 29, 100, 1., 3.);
    agv_color_pallete_set(clr, 2, 26, 87, 225, 1., 10.);
    agv_show(fig);
    agv_figure_delete(&fig);
    agx_matrix_delete(&mat);
    return 0;
}