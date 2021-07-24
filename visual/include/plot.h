/**
 * \file plot.h
 * @brief the library for data visualization
 * 
 * */

#ifndef __PLOT_H
#define __PLOT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief macro of the maximum RGB value
 * */
#define VRGB 255

/**
 * @brief canvas numbering for visualization
 * */
typedef enum e_canvas_type {AGV_PLOT, AGV_SCATTER, AGV_IMAGE, AGV_CONTOUR} AgvCanvasType;

/**
 * @brief color struct
 * */
typedef struct s_color {
    int r;
    int g;
    int b;
    double a;
    double val;
    int size;
} AgxColor;


/**
 * @brief plot data struct
 * */
typedef struct s_plot_data {
    AgxVector *vecx;
    AgxVector *vecy;
} AgxPlotData;

/**
 * @brief coordinate struct (double)
 * */
typedef struct s_coord_double {
    double x;
    double y;
} AgxCoordDouble;

/**
 * @brief coordinate struct (integer)
 * */
typedef struct s_coord_int {
    int x;
    int y;
} AgxCoordInt;

/**
 * @brief canvas struct
 * */
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

/**
 * @brief figure struct
 * */
typedef struct s_figure {
    int row;
    int col;
    int size;
    AgvCanvas *p_r_canvas;
} AgvFigure;

/**
 * @brief setting the color pallete of imshow canvas
 * */
void *agv_color_pallete_set(AgxColor *clr, int index, int r, int g, int b, double a, double val);

/**
 * @brief create a new figure struct (should use @ref agv_subplots instead)
 * @note need to be manually deleted using @ref agv_figure_delete
 * */
AgvFigure *agv_figure_new(int row, int col);

/**
 * @brief delete a figure
 * */
void agv_figure_delete(AgvFigure *fig);

/**
 * @brief Create a figure with subplots definition
 * */
AgvFigure *agv_subplots(int row, int col);

/**
 * @brief select a canvas from the existing figure
 * @note it is used for the input of the other functions
 * */
AgvCanvas *agv_set_canvas(AgvFigure *fig, int index);

/**
 * @brief plotting the data on a line
 * */
void *agv_plot(AgvCanvas *can, AgxVector *vecx, AgxVector *vecy);

/**
 * @brief plotting the data on some scattering bullets
 * */
void *agv_scatter(AgvCanvas *can, AgxVector *vecx, AgxVector *vecy);

/**
 * @brief imaging the matrix data
 * */
void *agv_imshow(AgvCanvas *can, AgxMatrix *mat);

/**
 * @brief set the size of color pallete from the existing canvas
 * */
AgxColor *agv_color_pallete_canvas_set_size(AgvCanvas *can, int line, int size);

/**
 * @brief x limit values of the canvas
 * */
void *agv_xlim(AgvCanvas *can, double min, double max);

/**
 * @brief y limit values of the canvas
 * */
void *agv_ylim(AgvCanvas *can, double min, double max);

/**
 * @brief construct the figure and show it
 * */
void agv_show(AgvFigure *fig);

/**
 * @brief set the color of plotting and scattering, and image (the color fill)
 * */
void *agv_set_color_alpha(AgvCanvas *can, int line, int red, int green, int blue, double alpha);

/**
 * @brief set the color of the boundary of scattering sircle and image
 * */
void *agv_set_color_alpha_line(AgvCanvas *can, int line, int red, int green, int blue, double alpha);

/**
 * @brief set the radius of scattering circle
 * */
void *agv_set_radius(AgvCanvas *can, int line, int radius);

/**
 * @brief set the thick of line, the boundary of image and scattering circle
 * */
void *agv_set_linewidth(AgvCanvas *can, int line, int linewidth);

/**
 * @brief true if showing grid, default is false
 * */
void *agv_set_grid(AgvCanvas *can, int boolean);

#ifdef __cplusplus
}
#endif

#endif