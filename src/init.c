#include "init.h"
#include <malloc.h>
#include <string.h>

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

