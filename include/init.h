#ifndef __INIT_H
#define __INIT_H

#ifdef __cplusplus
extern "C" {
#endif

enum e_bool {FALSE, TRUE};

typedef struct s_slice {
    int start;
    int step;
    int stop;
} AgxSlice;

void *agx_print_integer(int val);
void *agx_print_double(double val);
void *agx_print_string(char *val);
int agx_string_length_integer(int val);
int agx_string_length_string(char *str);
int agx_string_length_double(double val);
char *agx_string_from_double_set(char *set, double val);
char *agx_string_from_integer(int val);
void *agx_string_append_integer(char *target, int val, int isInitial);
char *agx_string_from_double(double val);
void *agx_string_append_double(char *target, double val, int isInitial);
void *agx_print_values(char *inbetween, char *end, char *fmt, ...);
void *agx_print_values_space(char *fmt, ...);
void *agx_print_values_new_line(char *fmt, ...);
#ifdef __cplusplus
}
#endif

#endif