/**
 * \file picture.h
 * @brief the library for picture manupulation
 * */

#ifndef __PICTURE_H
#define __PICTURE_H

#ifdef __cplusplus
extern "C" {
#endif

#define VRGB 255

typedef struct s_color {
    double r;
    double g;
    double b;
    double a;
} AgvColor;

typedef struct s_coord {
    double x;
    double y;
} AgxCoord;

typedef struct s_picture {
    cairo_t *cr;
    cairo_surface_t *surface;
    double rptu;
    AgxCoord size;
    AgxCoord origin;
} AgvPicture;

typedef struct s_text {
    AgvColor clr;
    char *text;
    double fontSize;
    AgxCoord loc;
} AgvText;

typedef struct s_line {
    AgvColor clr;
    double lineWidth;
    AgxCoord *p_r_loc;
    int size;
} AgvLine;

AgvPicture *agv_picture_new(int width, int height);
void agv_picture_delete(AgvPicture **pic);
int agv_picture_save(AgvPicture *pic, char *filename);
int agv_picture_input_text(AgvPicture *pic, AgvText *text);
int agv_picture_input_line(AgvPicture *pic, AgvLine *line);
void agv_picture_normalize(AgvPicture *pic, double ratioPixelToUnit);
void agv_picture_unit_max(AgvPicture *pic, AgxCoord *out);
void agv_picture_unit_to_pixel(AgvPicture *pic, AgxCoord *in, AgxCoord *out);
void agv_picture_coord_to_unit(AgvPicture *pic, AgxCoord *in, AgxCoord *out);
void agv_picture_coord_to_pixel(AgvPicture *pic, AgxCoord *in, AgxCoord *out);
void agv_picture_unit_set_width(AgvPicture *pic, double width);
void agv_picture_unit_set_height(AgvPicture *pic, double height);
void agv_picture_set_background(AgvPicture *pic, AgvColor *clr);
double agv_u2p(AgvPicture *pic, double in);
void agv_picture_set_origin(AgvPicture *pic, AgxCoord *origin);
void agv_picture_set_coord_origin(AgvPicture *pic, AgxCoord *origin);

/// text
AgvText *agv_picture_text_new(char *text, double x, double y);
AgvText *agv_picture_text_coord_new(AgvPicture *pic, char *text, AgxCoord *posText);
void agv_picture_text_set_font_size(AgvText *text, double fontSize);
void agv_picture_text_delete(AgvText **text);

/// line
AgvLine *agv_picture_line_new(AgxCoord *pointArray, int size);
AgvLine *agv_picture_line_coord_new(AgvPicture *pic, AgxCoord *pointArray, int size);
void agv_picture_line_set_line_width(AgvLine *line, double lineWidth);
void agv_picture_line_delete(AgvLine **line);

/// arc

/// circle

/// applied issues

/// manager


#ifdef __cplusplus
}
#endif

#endif