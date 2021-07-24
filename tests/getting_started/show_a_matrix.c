#include "angka.h"
#include "angkavisual.h"

int main() {
    AgxMatrix *mat = agx_matrix_new_random(100, 100, -10, 10);
    AgvFigure *fig = agv_subplots(1,1);
    agv_imshow(agv_set_canvas(fig, 0), mat);
    agv_show(fig);
    agv_figure_delete(fig);
    agx_matrix_delete(mat);
    return 0;
}