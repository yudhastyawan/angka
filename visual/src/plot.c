#include "init.h"
#include "standard.h"
#include "vector.h"
#include "matrix.h"
#include <malloc.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include "plot.h"

// start of static declarations
static void do_drawing(cairo_t *, GtkWidget *, gpointer);
static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data);
static void destroy(GtkWidget *widget, gpointer data);
// end of static declarations


AgvFigure *agv_figure_new(int row, int col) {
    AgvFigure *fig;
    fig = (AgvFigure *)malloc(sizeof(AgvFigure));
    fig->row = row;
    fig->col = col;
    fig->size = row*col;
    fig->p_r_canvas = (AgvCanvas *)malloc((fig->size)*sizeof(AgvCanvas));
    return fig;
}

void agv_figure_delete(AgvFigure *fig) {
    for (int i = 0; i < fig->size; i++) {
        if (fig->p_r_canvas[i].numOfVec != 0) {
            free(fig->p_r_canvas[i].p_r_type);
            free(fig->p_r_canvas[i].p_r_vecx);
            free(fig->p_r_canvas[i].p_r_vecy);
            free(fig->p_r_canvas[i].p_r_color);
            free(fig->p_r_canvas[i].p_r_linewidth);
        }
    }
    free(fig->p_r_canvas);
    free(fig);
}

AgvFigure *agv_subplots(int row, int col) {
    AgvFigure *fig = agv_figure_new(row, col);
    for (int i = 0; i < fig->size; i++) {
        fig->p_r_canvas[i].numOfVec = 0;
    }
    return fig;
}

AgvCanvas *agv_set_canvas(AgvFigure *fig, int index) {
    return &(fig->p_r_canvas[index]);
}

void *agv_allocation(AgvCanvas *can, AgxVector *vecx, AgxVector *vecy){
    if (can->numOfVec == 0) {
        can->numOfVec++;
        can->p_r_type = (int *)malloc(can->numOfVec*sizeof(int));
        can->p_r_linewidth = (int *)malloc(can->numOfVec*sizeof(int));
        can->p_r_radius = (int *)malloc(can->numOfVec*sizeof(int));
        can->p_r_color = (AgxColor *)malloc(can->numOfVec*sizeof(AgxColor));
        can->p_r_color_outside = (AgxColor *)malloc(can->numOfVec*sizeof(AgxColor));
        can->p_r_vecx = (AgxVector **)malloc(can->numOfVec*sizeof(AgxVector *));
        can->p_r_vecy = (AgxVector **)malloc(can->numOfVec*sizeof(AgxVector *));
        can->min = (AgxCoordDouble) {.x = agx_vector_min(vecx), .y = agx_vector_min(vecy)};
        can->max = (AgxCoordDouble) {.x = agx_vector_max(vecx), .y = agx_vector_max(vecy)};
    } else {
        can->numOfVec++;
        can->p_r_type = (int *)realloc(can->p_r_type, can->numOfVec*sizeof(int));
        can->p_r_linewidth = (int *)realloc(can->p_r_linewidth, can->numOfVec*sizeof(int));
        can->p_r_radius = (int *)realloc(can->p_r_radius, can->numOfVec*sizeof(int));
        can->p_r_color = (AgxColor *)realloc(can->p_r_color, can->numOfVec*sizeof(AgxColor));
        can->p_r_color_outside = (AgxColor *)realloc(can->p_r_color_outside, can->numOfVec*sizeof(AgxColor));
        can->p_r_vecx = (AgxVector **)realloc(can->p_r_vecx, can->numOfVec*sizeof(AgxVector *));
        can->p_r_vecy = (AgxVector **)realloc(can->p_r_vecy, can->numOfVec*sizeof(AgxVector *));
    }
}

void *agv_plot(AgvCanvas *can, AgxVector *vecx, AgxVector *vecy){
    agv_allocation(can, vecx, vecy);
    can->p_r_type[can->numOfVec - 1] = AGV_PLOT;
    can->p_r_linewidth[can->numOfVec - 1] = 5;
    can->p_r_color[can->numOfVec - 1] = (AgxColor) {.r = 0, .g = 0, .b = 0, .a = 1.};
    can->p_r_vecx[can->numOfVec - 1] = vecx;
    can->p_r_vecy[can->numOfVec - 1] = vecy;
    can->grid = 0;
}

void *agv_scatter(AgvCanvas *can, AgxVector *vecx, AgxVector *vecy){
    agv_allocation(can, vecx, vecy);
    can->p_r_type[can->numOfVec - 1] = AGV_SCATTER;
    can->p_r_linewidth[can->numOfVec - 1] = 1;
    can->p_r_radius[can->numOfVec - 1] = 5;
    can->p_r_color[can->numOfVec - 1] = (AgxColor) {.r = 0, .g = 0, .b = 0, .a = 1.};
    can->p_r_color_outside[can->numOfVec - 1] = (AgxColor) {.r = 0, .g = 0, .b = 0, .a = 1.};
    can->p_r_vecx[can->numOfVec - 1] = vecx;
    can->p_r_vecy[can->numOfVec - 1] = vecy;
    can->grid = 0;
}

void *agv_xlim(AgvCanvas *can, double min, double max) {
    can->min.x = min;
    can->max.x = max;
}

void *agv_ylim(AgvCanvas *can, double min, double max) {
    can->min.y = min;
    can->max.y = max;
}

void *agv_set_grid(AgvCanvas *can, int boolean) {
    can->grid = boolean;
}

void *agv_set_color_alpha(AgvCanvas *can, int line, int red, int green, int blue, double alpha) {
    can->p_r_color[line].r = red;
    can->p_r_color[line].g = green;
    can->p_r_color[line].b = blue;
    can->p_r_color[line].a = alpha;
}

void *agv_set_color_alpha_line_scatter(AgvCanvas *can, int line, int red, int green, int blue, double alpha) {
    can->p_r_color_outside[line].r = red;
    can->p_r_color_outside[line].g = green;
    can->p_r_color_outside[line].b = blue;
    can->p_r_color_outside[line].a = alpha;
}

void *agv_set_radius(AgvCanvas *can, int line, int radius) {
    can->p_r_radius[line] = radius;
}

void *agv_set_linewidth(AgvCanvas *can, int line, int linewidth) {
    can->p_r_linewidth[line] = linewidth;
}

void agv_show(AgvFigure *fig) {
    GtkWidget *window;

    gtk_init(0, NULL);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    GtkWidget *gridarea = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), gridarea);

    GtkWidget **r_darea = (GtkWidget**)malloc(fig->size*sizeof(GtkWidget*));

    int i_row, i_col;
    for (int i = 0; i < fig->size; i++) {
        i_col = i%fig->col;
        i_row = i/fig->col;
        r_darea[i] = gtk_drawing_area_new();
        gtk_widget_set_hexpand(r_darea[i], TRUE);
        gtk_widget_set_vexpand(r_darea[i], TRUE);
        gtk_grid_attach(GTK_GRID(gridarea),r_darea[i],i_col,i_row,1,1);
        fig->p_r_canvas[i].col = fig->col;
        fig->p_r_canvas[i].row = fig->row;
        fig->p_r_canvas[i].index = i;
        g_signal_connect(G_OBJECT(r_darea[i]), "draw", G_CALLBACK(on_draw_event), &(fig->p_r_canvas[i]));
    }

    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(destroy), r_darea);

    gtk_widget_show_all(window);
    gtk_main();
}

void agv_data_to_canvas(AgxCoordInt *winMin, AgxCoordInt *winMax, AgxCoordDouble *input, AgxCoordInt *output, AgxCoordDouble *dataMin, AgxCoordDouble *dataMax) {
    double ratio;
    ratio = (input->x - dataMin->x)/(dataMax->x - dataMin->x);
    output->x = (int) (ratio * (winMax->x - winMin->x) + winMin->x);

    ratio = (input->y - dataMin->y)/(dataMax->y - dataMin->y);
    output->y = - (int) (ratio * (winMax->y - winMin->y) + winMin->y);
}

void agv_create_line(cairo_t *cr, AgxCoordDouble *points, AgxCoordInt **window, AgxCoordDouble **datlim, int lineWidth){
    AgxCoordInt output;
    cairo_set_line_width(cr, lineWidth);
    agv_data_to_canvas(window[0], window[1], &points[0], &output, datlim[0], datlim[1]);
    cairo_move_to(cr, output.x, output.y);
    agv_data_to_canvas(window[0], window[1], &points[1], &output, datlim[0], datlim[1]);
    cairo_line_to(cr, output.x, output.y);
    cairo_stroke(cr);
}

void agv_create_multiline(cairo_t *cr, AgxVector *vecx, AgxVector *vecy, AgxCoordInt **window, AgxCoordDouble **datlim, int lineWidth){
    AgxCoordInt output;
    AgxCoordDouble input;
    cairo_set_line_width(cr, lineWidth);
    
    input.x = vecx->p_r_nums[0];
    input.y = vecy->p_r_nums[0];
    agv_data_to_canvas(window[0], window[1], &input, &output, datlim[0], datlim[1]);
    cairo_move_to(cr, output.x, output.y);
    for (int i = 1; i < vecx->size; i++) {
        input.x = vecx->p_r_nums[i];
        input.y = vecy->p_r_nums[i];
        agv_data_to_canvas(window[0], window[1], &input, &output, datlim[0], datlim[1]);
        cairo_line_to(cr, output.x, output.y);
    }
    cairo_stroke(cr);
}

void agv_create_text(cairo_t *cr, AgxCoordDouble *point, AgxCoordInt **window, AgxCoordDouble **datlim, double fontSize, char *text){
    AgxCoordInt output;
    cairo_set_font_size(cr, fontSize);
    agv_data_to_canvas(window[0], window[1], point, &output, datlim[0], datlim[1]);
    cairo_move_to(cr, output.x, output.y);
    cairo_show_text(cr, text);
    cairo_stroke(cr);
}

void agv_create_circle(cairo_t *cr, AgxCoordDouble *point, AgxCoordInt **window, AgxCoordDouble **datlim, double radius, AgxColor *color_fill, AgxColor *color_outside){
    AgxCoordInt output;
    agv_data_to_canvas(window[0], window[1], point, &output, datlim[0], datlim[1]);
    cairo_arc(cr, output.x, output.y, radius, 0, 2*M_PI);
    cairo_set_source_rgba(cr, (double)color_outside->r/VRGB, (double)color_outside->g/VRGB, (double)color_outside->b/VRGB, color_outside->a);
    cairo_stroke_preserve(cr);
    cairo_set_source_rgba(cr, (double)color_fill->r/VRGB, (double)color_fill->g/VRGB, (double)color_fill->b/VRGB, color_fill->a);
    cairo_fill(cr);
}

void agv_create_multicircle(cairo_t *cr, AgxVector *vecx, AgxVector *vecy, AgxCoordInt **window, AgxCoordDouble **datlim, double radius, int lineWidth, AgxColor *color_fill, AgxColor *color_outside){
    AgxCoordInt output;
    AgxCoordDouble input;
    cairo_set_line_width(cr, lineWidth);
    for (int i = 0; i < vecx->size; i++) {
        input.x = vecx->p_r_nums[i];
        input.y = vecy->p_r_nums[i];
        agv_create_circle(cr, &input, window, datlim, radius, color_fill, color_outside);        
    }
}

void agv_create_text_addxy(cairo_t *cr, AgxCoordDouble *point, AgxCoordInt **window, AgxCoordDouble **datlim, double fontSize, char *text, int x, int y){
    AgxCoordInt output;
    cairo_set_font_size(cr, fontSize);
    agv_data_to_canvas(window[0], window[1], point, &output, datlim[0], datlim[1]);
    cairo_move_to(cr, output.x + x, output.y + y);
    cairo_show_text(cr, text);
    cairo_stroke(cr);
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    do_drawing(cr, widget, user_data);
    return FALSE;
}

static void do_drawing(cairo_t *cr, GtkWidget *widget, gpointer data) {
    AgvCanvas *can = data;
    AgxCoordDouble *dataMin = &(can->min);
    AgxCoordDouble *dataMax = &(can->max);
    AgxCoordDouble *datLim[] = {dataMin, dataMax};

    int winx, winy;
    AgxCoordDouble input;
    AgxCoordDouble points[2];
    AgxCoordInt output;

    GtkWidget *win = gtk_widget_get_toplevel(widget);
    gtk_window_get_size(GTK_WINDOW(win), &winx, &winy);
    AgxCoordInt winMin = {.x = -winx/(can->col*2), .y = -winy/(can->row*2)};
    AgxCoordInt winMax = {.x = winx/(can->col*2), .y = winy/(can->row*2)};
    AgxCoordInt *window[] = {&winMin, &winMax};

    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);
    cairo_translate(cr, winx/(can->col*2), winy/(can->row*2));
    cairo_scale(cr, 0.8, 0.8);

    cairo_set_source_rgb(cr, 0, 0, 0);
    points[0] = (AgxCoordDouble){.x = dataMin->x, .y = dataMin->y};
    points[1] = (AgxCoordDouble){.x = dataMax->x, .y = dataMin->y};
    agv_create_line(cr, points, window, datLim, 3);

    points[0] = (AgxCoordDouble){.x = 0., .y = dataMin->y};
    points[1] = (AgxCoordDouble){.x = 0., .y = dataMax->y};
    agv_create_line(cr, points, window, datLim, 3);

    AgxVector *xlbl;
    xlbl = agx_vector_new_arange_double(dataMin->x, 1., dataMax->x);
    for (int i = 0; i < xlbl->size; i++) {
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
        input = (AgxCoordDouble){.x = xlbl->p_r_nums[i], .y = dataMin->y};
        agv_create_text_addxy(cr, &input, window, datLim, 20, agx_string_from_double_set("%.1f", xlbl->p_r_nums[i]), 0, winMax.y/10);

        if (can->grid == TRUE) {
            cairo_set_source_rgba(cr, 0, 0, 0, 0.2);
            points[0] = (AgxCoordDouble){.x = xlbl->p_r_nums[i], .y = dataMin->y};
            points[1] = (AgxCoordDouble){.x = xlbl->p_r_nums[i], .y = dataMax->y};
            agv_create_line(cr, points, window, datLim, 1);
        }
    }
    agx_vector_delete(xlbl);

    xlbl = agx_vector_new_arange_double(dataMin->y, 1., dataMax->y);
    for (int i = 0; i < xlbl->size; i++) {
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
        input = (AgxCoordDouble){.x = dataMin->x, .y = xlbl->p_r_nums[i]};
        agv_create_text_addxy(cr, &input, window, datLim, 20, agx_string_from_double_set("%.2f", xlbl->p_r_nums[i]), -1*winMax.x/5, 0);

        if (can->grid == TRUE) {
            cairo_set_source_rgba(cr, 0, 0, 0, 0.2);
            points[0] = (AgxCoordDouble){.x = dataMin->x, .y = xlbl->p_r_nums[i]};
            points[1] = (AgxCoordDouble){.x = dataMax->x, .y = xlbl->p_r_nums[i]};
            agv_create_line(cr, points, window, datLim, 1);
        }
    }
    agx_vector_delete(xlbl);

    for (int i = 0; i < can->numOfVec; i++) {
        if (can->p_r_type[i] == AGV_PLOT) {
            cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
            cairo_set_line_join(cr, CAIRO_LINE_JOIN_BEVEL);
            cairo_set_source_rgba(cr, (double)can->p_r_color[i].r/VRGB, (double)can->p_r_color[i].g/VRGB, (double)can->p_r_color[i].b/VRGB, can->p_r_color[i].a);
            agv_create_multiline(cr, can->p_r_vecx[i], can->p_r_vecy[i], window, datLim, can->p_r_linewidth[i]);
        } else if (can->p_r_type[i] == AGV_SCATTER) {
            agv_create_multicircle(cr, can->p_r_vecx[i], can->p_r_vecy[i], window, datLim, (double)can->p_r_radius[i], can->p_r_linewidth[i], &(can->p_r_color[i]), &(can->p_r_color_outside[i]));
        }
    }
}

static void destroy(GtkWidget *widget, gpointer data) {
    GtkWidget **r_darea = data;
    free(r_darea);
    gtk_main_quit();
}