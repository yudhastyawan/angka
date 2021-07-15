#include "init.h"
#include <malloc.h>
#include <string.h>

void *getPrintInteger(int val) {
    printf("%d\n", val);
}

void *getPrintDouble(double val) {
    printf("%f\n", val);
}

void *getPrintString(char *val) {
    printf("%s\n", val);
}

int getStringLengthInteger(int val) {
    return snprintf(0,0,"%d", val)+1;
}

int getStringLengthString(char *str) {
    return snprintf(0,0,"%s", str);
}

int getStringLengthDouble(double val) {
    return snprintf(0,0,"%f", val);
}

char *getStringFromInteger(int val) {
    char *str;
    int len = getStringLengthInteger(val);
    str = malloc(len);
    snprintf(str, len, "%d", val);
    return str;
}

void *getStringAppendInteger(char *target, int val, int isInitial) {
    char *str = getStringFromInteger(val);
    if (isInitial == 1) {
        strcpy(target, str);
    } else {
        strcat(target, str);
    }
    free(str);
}

char *getStringFromDouble(double val) {
    char *str;
    int len = getStringLengthDouble(val);
    str = malloc(len);
    snprintf(str, len, "%f", val);
    return str;
}

void *getStringAppendDouble(char *target, double val, int isInitial) {
    char *str = getStringFromDouble(val);
    if (isInitial == 1) {
        strcpy(target, str);
    } else {
        strcat(target, str);
    }
    free(str);
}

