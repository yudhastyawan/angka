#include "init.h"
#include "standard.h"
#include "vector.h"
#include "matrix.h"
#include "plot.h"
#include <cairo.h>
#include <gtk/gtk.h>

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

void agv_data_to_canvas(AgxCoordInt *winMin, AgxCoordInt *winMax, AgxCoordDouble *input, AgxCoordInt *output, AgxCoordDouble *dataMin, AgxCoordDouble *dataMax) {
    double ratio;
    ratio = (input->x - dataMin->x)/(dataMax->x - dataMin->x);
    output->x = (int) (ratio * (winMax->x - winMin->x) + winMin->x);

    ratio = (input->y - dataMin->y)/(dataMax->y - dataMin->y);
    output->y = winMax->y - (int) (ratio * (winMax->y - winMin->y) + winMin->y);
}

static void do_drawing(cairo_t *, GtkWidget *, gpointer);

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    do_drawing(cr, widget, user_data);
    return FALSE;
}

static void do_drawing(cairo_t *cr, GtkWidget *widget, gpointer data) {
    GtkWidget *win = gtk_widget_get_toplevel(widget);

    AgxCoordInt winMax;
    gtk_window_get_size(GTK_WINDOW(win), &winMax.x, &winMax.y);
    AgxCoordInt winMin = {.x = 0, .y = 0};

    AgxCoordDouble dataMin = {.x = 0., .y = -10.};
    AgxCoordDouble dataMax = {.x = 10., .y = 10.};
    
    AgxPlotData *user_data = data;

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_BEVEL);
    cairo_set_line_width(cr, 5);
    AgxCoordDouble input;
    AgxCoordInt output;
    input.x = user_data->vecx->p_r_nums[0];
    input.y = user_data->vecy->p_r_nums[0];
    agv_data_to_canvas(&winMin, &winMax, &input, &output, &dataMin, &dataMax);
    cairo_move_to(cr, output.x, output.y);
    for (int i = 1; i < user_data->vecx->size; i++) {
        input.x = user_data->vecx->p_r_nums[i];
        input.y = user_data->vecy->p_r_nums[i];
        agv_data_to_canvas(&winMin, &winMax, &input, &output, &dataMin, &dataMax);
        cairo_line_to(cr, output.x, output.y);
    }
    cairo_stroke(cr);
}

void agv_plot(AgxVector *vecx, AgxVector *vecy) {
    GtkWidget *window, *darea;
    AgxPlotData plotData;
    plotData.vecx = vecx;
    plotData.vecy = vecy;

    gtk_init(0, NULL);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), darea);

    g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw_event), &plotData);
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();
}