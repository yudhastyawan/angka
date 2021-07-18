#include "init.h"
#include <malloc.h>
#include <string.h>
#include <stdarg.h>

void *agx_print_integer(int val) {
    printf("%d\n", val);
}

void *agx_print_double(double val) {
    printf("%f\n", val);
}

void *agx_print_string(char *val) {
    printf("%s\n", val);
}

int agx_string_length_integer(int val) {
    return snprintf(0,0,"%d", val)+1;
}

int agx_string_length_string(char *str) {
    return snprintf(0,0,"%s", str);
}

int agx_string_length_double(double val) {
    return snprintf(0,0,"%f", val);
}

char *agx_string_from_integer(int val) {
    char *str;
    int len = agx_string_length_integer(val);
    str = malloc(len);
    snprintf(str, len, "%d", val);
    return str;
}

void *agx_string_append_integer(char *target, int val, int isInitial) {
    char *str = agx_string_from_integer(val);
    if (isInitial == 1) {
        strcpy(target, str);
    } else {
        strcat(target, str);
    }
    free(str);
}

char *agx_string_from_double(double val) {
    char *str;
    int len = agx_string_length_double(val);
    str = malloc(len);
    snprintf(str, len, "%f", val);
    return str;
}

char *agx_string_from_double_set(char *set, double val) {
    char *str;
    int len = agx_string_length_double(val);
    str = malloc(len);
    snprintf(str, len, set, val);
    return str;
}

void *agx_string_append_double(char *target, double val, int isInitial) {
    char *str = agx_string_from_double(val);
    if (isInitial == 1) {
        strcpy(target, str);
    } else {
        strcat(target, str);
    }
    free(str);
}

static void *agx_print_v(char *inbetween, char *end, char *fmt, va_list args) {
    while (*fmt != '\0') {
        if (*fmt == 'd') {
            int val = va_arg(args, int);
            printf("%d%s", val, inbetween);
        } else if (*fmt == 'c') {
            int val = va_arg(args, int);
            printf("%c%s", val, inbetween);
        } else if (*fmt == 'f') {
            double val = va_arg(args, double);
            printf("%f%s", val, inbetween);
        } else if (*fmt == 's') {
            char * val = va_arg(args, char *);
            printf("%s%s", val, inbetween);
        }
        ++fmt;
    }
    printf("%s", end);
}

void *agx_print_values(char *inbetween, char *end, char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    agx_print_v(inbetween, end, fmt, args);
    va_end(args);
}

void *agx_print_values_space(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    agx_print_v(" ", "\n", fmt, args);
    va_end(args);
}

void *agx_print_values_new_line(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    agx_print_v("\n", " ", fmt, args);
    va_end(args);
}