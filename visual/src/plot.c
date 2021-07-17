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
    output->y = - (int) (ratio * (winMax->y - winMin->y) + winMin->y);
}

static void do_drawing(cairo_t *, GtkWidget *, gpointer);

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    do_drawing(cr, widget, user_data);
    return FALSE;
}

static void do_drawing(cairo_t *cr, GtkWidget *widget, gpointer data) {
    GtkWidget *win = gtk_widget_get_toplevel(widget);
    int winx, winy;
    AgxCoordDouble input;
    AgxCoordInt output;

    gtk_window_get_size(GTK_WINDOW(win), &winx, &winy);
    AgxCoordInt winMin = {.x = 0 - (winx/2), .y = 0 - (winy/2)};
    AgxCoordInt winMax = {.x = 0 + (winx/2), .y = 0 + (winy/2)};
    
    AgxPlotData *user_data = data;

    AgxCoordDouble dataMin = {.x = agx_vector_min(user_data->vecx), .y = agx_vector_min(user_data->vecy)};
    AgxCoordDouble dataMax = {.x = agx_vector_max(user_data->vecx), .y = agx_vector_max(user_data->vecy)};

    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);
    cairo_translate(cr, winx/2, winy/2);
    cairo_scale(cr, 0.8, 0.8);

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 3);
    input = (AgxCoordDouble){.x = dataMin.x, .y = dataMin.y};
    agv_data_to_canvas(&winMin, &winMax, &input, &output, &dataMin, &dataMax);
    cairo_move_to(cr, output.x, output.y);
    input = (AgxCoordDouble){.x = dataMax.x, .y = dataMin.y};
    agv_data_to_canvas(&winMin, &winMax, &input, &output, &dataMin, &dataMax);
    cairo_line_to(cr, output.x, output.y);
    cairo_stroke(cr);

    input = (AgxCoordDouble){.x = 0., .y = dataMin.y};
    agv_data_to_canvas(&winMin, &winMax, &input, &output, &dataMin, &dataMax);
    cairo_move_to(cr, output.x, output.y);
    input = (AgxCoordDouble){.x = 0., .y = dataMax.y};
    agv_data_to_canvas(&winMin, &winMax, &input, &output, &dataMin, &dataMax);
    cairo_line_to(cr, output.x, output.y);
    cairo_stroke(cr);

    AgxVector *xlbl = agx_vector_new_linspace(dataMin.x, dataMax.x, 10);
    for (int i = 0; i < 10; i++) {
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size(cr, 20.0);

        input = (AgxCoordDouble){.x = xlbl->p_r_nums[i], .y = dataMin.y};
        agv_data_to_canvas(&winMin, &winMax, &input, &output, &dataMin, &dataMax);
        cairo_move_to(cr, output.x, output.y + 20);
        cairo_show_text(cr, agx_string_from_double_set("%.2f",xlbl->p_r_nums[i]));

        cairo_set_source_rgba(cr, 0, 0, 0, 0.2);
        cairo_set_line_width(cr, 1);
        input = (AgxCoordDouble){.x = xlbl->p_r_nums[i], .y = dataMin.y};
        agv_data_to_canvas(&winMin, &winMax, &input, &output, &dataMin, &dataMax);
        cairo_move_to(cr, output.x, output.y);
        input = (AgxCoordDouble){.x = xlbl->p_r_nums[i], .y = dataMax.y};
        agv_data_to_canvas(&winMin, &winMax, &input, &output, &dataMin, &dataMax);
        cairo_line_to(cr, output.x, output.y);
        cairo_stroke(cr);
    }
    agx_vector_delete(xlbl);

    AgxVector *ylbl = agx_vector_new_linspace(dataMin.y, dataMax.y, 10);
    for (int i = 0; i < 10; i++) {
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size(cr, 20.0);

        input = (AgxCoordDouble){.x = dataMin.x, .y = ylbl->p_r_nums[i]};
        agv_data_to_canvas(&winMin, &winMax, &input, &output, &dataMin, &dataMax);
        cairo_move_to(cr, output.x - 60, output.y);
        cairo_show_text(cr, agx_string_from_double_set("%.2f",ylbl->p_r_nums[i]));

        cairo_set_source_rgba(cr, 0, 0, 0, 0.2);
        cairo_set_line_width(cr, 1);
        input = (AgxCoordDouble){.x = dataMin.x, .y = ylbl->p_r_nums[i]};
        agv_data_to_canvas(&winMin, &winMax, &input, &output, &dataMin, &dataMax);
        cairo_move_to(cr, output.x, output.y);
        input = (AgxCoordDouble){.x = dataMax.y, .y = ylbl->p_r_nums[i]};
        agv_data_to_canvas(&winMin, &winMax, &input, &output, &dataMin, &dataMax);
        cairo_line_to(cr, output.x, output.y);
        cairo_stroke(cr);
    }
    agx_vector_delete(ylbl);

    cairo_set_source_rgb(cr, 0, 0, 1);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_BEVEL);
    cairo_set_line_width(cr, 3);
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

static void destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
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
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(destroy), &plotData);

    gtk_widget_show_all(window);
    gtk_main();
}