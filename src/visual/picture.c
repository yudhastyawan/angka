#include <stdio.h>
#include <malloc.h>
#include <cairo.h>
#include "picture.h"

AgvPicture *agv_picture_new(int width, int height) {
    AgvPicture *pic = malloc(sizeof(AgvPicture));
    if (pic == NULL) {
        fprintf(stderr, "pic cannot be allocated\n");
        return NULL;
    }
    pic->surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    pic->cr = cairo_create(pic->surface);
    pic->rptu = 1.;
    pic->size = (AgxCoord) {.x = width, .y = height};
    pic->origin = (AgxCoord) {.x = 0., .y = height};
    return pic;
}

void agv_picture_delete(AgvPicture **pic) {
    if (*pic == NULL) {
        fprintf(stderr, "pic is NULL\n");
        return;
    }
    cairo_destroy((*pic)->cr);
    cairo_surface_destroy((*pic)->surface);
    free(*pic);
    *pic = NULL;
}

int agv_picture_save(AgvPicture *pic, char *filename) {
    if (cairo_surface_write_to_png(pic->surface, filename) != 0) {
        fprintf(stderr, "picture cannot be saved\n");
        return -1;
    }
    return 0;
}

int agv_picture_input_text(AgvPicture *pic, AgvText *text) {
    cairo_set_source_rgba(pic->cr, text->clr.r/VRGB, text->clr.g/VRGB, text->clr.b/VRGB, text->clr.a);
    cairo_select_font_face(pic->cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(pic->cr, text->fontSize);
    cairo_move_to(pic->cr, text->loc.x, text->loc.y);
    cairo_show_text(pic->cr, text->text);
    return 0;
}

AgvText *agv_picture_text_new(char *text, double x, double y) {
    AgvText *txt = malloc(sizeof(AgvText));
    if (txt == NULL) {
        fprintf(stderr, "txt cannot be allocated\n");
        return NULL;
    }
    txt->text = text;
    txt->loc = (AgxCoord){.x = x, .y = y};
    txt->clr = (AgvColor) {.r = 0., .g = 0., .b = 0., .a = 1.};
    txt->fontSize = 40.0;
    return txt;
}

AgvText *agv_picture_text_coord_new(AgvPicture *pic, char *text, AgxCoord *posText) {
    AgxCoord pxText;
    agv_picture_coord_to_pixel(pic, posText, &pxText);
    AgvText *txt = agv_picture_text_new(text, pxText.x, pxText.y); ///<- position in pixel
    return txt;
}

void agv_picture_text_set_font_size(AgvText *text, double fontSize) {
    text->fontSize = fontSize;
}

void agv_picture_text_delete(AgvText **text) {
    if (*text == NULL) {
        fprintf(stderr, "text is NULL\n");
        return;
    }
    free(*text);
    *text = NULL;
}

void agv_picture_normalize(AgvPicture *pic, double ratioPixelToUnit) {
    pic->rptu = ratioPixelToUnit;
}

void agv_picture_unit_max(AgvPicture *pic, AgxCoord *out) {
    out->x = pic->size.x / pic->rptu;
    out->y = pic->size.y / pic->rptu;
}

void agv_picture_unit_to_pixel(AgvPicture *pic, AgxCoord *in, AgxCoord *out) {
    out->x = in->x * pic->rptu;
    out->y = in->y * pic->rptu;
}

void agv_picture_coord_to_unit(AgvPicture *pic, AgxCoord *in, AgxCoord *out) {
    out->x = pic->origin.x / pic->rptu + in->x;
    out->y = pic->origin.y / pic->rptu - in->y;
}

void agv_picture_coord_to_pixel(AgvPicture *pic, AgxCoord *in, AgxCoord *out) {
    AgxCoord unit;
    agv_picture_coord_to_unit(pic, in, &unit);
    agv_picture_unit_to_pixel(pic, &unit, out);
}

void agv_picture_unit_set_width(AgvPicture *pic, double width) {
    pic->rptu = pic->size.x / width;
}

void agv_picture_unit_set_height(AgvPicture *pic, double height) {
    pic->rptu = pic->size.y / height;
}

void agv_picture_set_background(AgvPicture *pic, AgvColor *clr) {
    cairo_set_source_rgba(pic->cr, clr->r/VRGB, clr->g/VRGB, clr->b/VRGB, clr->a);
    cairo_paint(pic->cr);
}

double agv_u2p(AgvPicture *pic, double in) {
    double out = in * pic->rptu;
    return out;
}

void agv_picture_set_origin(AgvPicture *pic, AgxCoord *origin) {
    pic->origin = *origin;
}

void agv_picture_set_coord_origin(AgvPicture *pic, AgxCoord *origin) {
    AgxCoord pxOri;
    agv_picture_coord_to_pixel(pic, origin, &pxOri);
    agv_picture_set_origin(pic, &pxOri);
}

AgvLine *agv_picture_line_new(AgxCoord *pointArray, int size) {
    AgvLine *line = malloc(sizeof(AgvLine));
    if (line == NULL) {
        fprintf(stderr, "line cannot be allocated\n");
        return NULL;
    }
    line->clr = (AgvColor) {.r = 0., .g = 0., .b = 0., .a = 1.};
    line->lineWidth = 5.0;
    line->size = size;
    line->p_r_loc = malloc(size * sizeof(AgxCoord));
    if (line->p_r_loc == NULL) {
        fprintf(stderr, "line->p_r_loc cannot be allocated\n");
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        line->p_r_loc[i] = pointArray[i];
    }
    return line;
}

AgvLine *agv_picture_line_coord_new(AgvPicture *pic, AgxCoord *pointArray, int size) {
    AgxCoord *pxLine = malloc(size*sizeof(pxLine));
    if (pxLine == NULL) {
        fprintf(stderr, "pxLine cannot be allocated\n");
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        agv_picture_coord_to_pixel(pic, &(pointArray[i]), &(pxLine[i]));
    }
    AgvLine *line = agv_picture_line_new(pxLine, size);
    free(pxLine);
    return line;
}

void agv_picture_line_set_line_width(AgvLine *line, double lineWidth) {
    line->lineWidth = lineWidth;
}

void agv_picture_line_delete(AgvLine **line) {
    if (*line == NULL) {
        fprintf(stderr, "line is NULL\n");
        return;
    }
    free((*line)->p_r_loc);
    free(*line);
    *line = NULL;
}

int agv_picture_input_line(AgvPicture *pic, AgvLine *line) {
    cairo_set_source_rgba(pic->cr, line->clr.r/VRGB, line->clr.g/VRGB, line->clr.b/VRGB, line->clr.a);
    cairo_set_line_width(pic->cr, line->lineWidth);
    cairo_move_to(pic->cr, line->p_r_loc[0].x, line->p_r_loc[0].y);
    for (int i = 1; i < line->size; i++) {
        cairo_line_to(pic->cr, line->p_r_loc[i].x, line->p_r_loc[i].y);
    }
    cairo_stroke(pic->cr);
    return 0;
}