#ifndef __PLOT_H
#define __PLOT_H

#ifdef __cplusplus
extern "C" {
#endif

#define VRGB 255

typedef enum e_canvas_type {AGV_PLOT, AGV_SCATTER, AGV_IMAGE, AGV_CONTOUR} AgvCanvasType;

typedef struct s_color {
    int r;
    int g;
    int b;
    double a;
    double val;
    int size;
} AgxColor;

typedef struct s_plot_data {
    AgxVector *vecx;
    AgxVector *vecy;
} AgxPlotData;

typedef struct s_coord_double {
    double x;
    double y;
} AgxCoordDouble;

typedef struct s_coord_int {
    int x;
    int y;
} AgxCoordInt;

typedef struct s_canvas {
    int *p_r_type;
    int *p_r_linewidth;
    int *p_r_radius;
    int row;
    int col;
    int index;
    int grid;
    AgxCoordDouble min;
    AgxCoordDouble max;
    AgxVector **p_r_vecx;
    AgxVector **p_r_vecy;
    AgxMatrix **p_r_mat;
    AgxColor *p_r_color;
    AgxColor *p_r_color_outside;
    AgxColor **p_r_color_pallete;
    int numOfVec;
} AgvCanvas;

typedef struct s_figure {
    int row;
    int col;
    int size;
    AgvCanvas *p_r_canvas;
} AgvFigure;

void *agv_color_pallete_set(AgxColor *clr, int index, int r, int g, int b, double a, double val);
AgvFigure *agv_figure_new(int row, int col);
void agv_figure_delete(AgvFigure *fig);

/**
 * @brief Create a figure with subplots definition
 * @details see my example at @include main_1.c
 * */
AgvFigure *agv_subplots(int row, int col);
AgvCanvas *agv_set_canvas(AgvFigure *fig, int index);
void *agv_plot(AgvCanvas *can, AgxVector *vecx, AgxVector *vecy);
void *agv_scatter(AgvCanvas *can, AgxVector *vecx, AgxVector *vecy);
void *agv_imshow(AgvCanvas *can, AgxMatrix *mat);
AgxColor *agv_color_pallete_canvas_set(AgvCanvas *can, int line, int size);
void *agv_xlim(AgvCanvas *can, double min, double max);
void *agv_ylim(AgvCanvas *can, double min, double max);
void agv_show(AgvFigure *fig);
void *agv_set_color_alpha(AgvCanvas *can, int line, int red, int green, int blue, double alpha);
void *agv_set_color_alpha_line_scatter(AgvCanvas *can, int line, int red, int green, int blue, double alpha);
void *agv_set_radius(AgvCanvas *can, int line, int radius);
void *agv_set_linewidth(AgvCanvas *can, int line, int linewidth);
void *agv_set_grid(AgvCanvas *can, int boolean);

#ifdef __cplusplus
}
#endif

#endif