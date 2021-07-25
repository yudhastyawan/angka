%include base.i

%include "plot.h"

%extend s_figure {
    s_figure(int dim1, int dim2) {
        AgvFigure *fig = agv_subplots(dim1, dim2);
        return fig;
    }

    ~s_figure() {
        agv_figure_delete($self);
    }

    void plot(int canvas, AgxVector *vecx, AgxVector *vecy) {
        agv_plot(agv_set_canvas($self, canvas), vecx, vecy);
    }

    void scatter(int canvas, AgxVector *vecx, AgxVector *vecy) {
        agv_scatter(agv_set_canvas($self, canvas), vecx, vecy);
    }

    void imshow(int canvas, AgxMatrix *mat) {
        agv_imshow(agv_set_canvas($self, canvas), mat);
    }

    void show() {
        agv_show($self);
    }
}