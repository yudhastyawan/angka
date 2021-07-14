#include "init.h"
#include <malloc.h>
#include <string.h>

void *Integer_Print(int val) {
    printf("%d\n", val);
}

void *Double_Print(double val) {
    printf("%f\n", val);
}

int StringLength_Integer(int val) {
    return snprintf(0,0,"%d", val)+1;
}

int StringLength_String(char *str) {
    return snprintf(0,0,"%s", str);
}

int StringLength_Double(double val) {
    return snprintf(0,0,"%f", val);
}

char *String_FromInteger(int val) {
    char *str;
    int len = StringLength_Integer(val);
    str = malloc(len);
    snprintf(str, len, "%d", val);
    return str;
}

void *String_Append_Integer(char *target, int val, int isInitial) {
    char *str = String_FromInteger(val);
    if (isInitial == 1) {
        strcpy(target, str);
    } else {
        strcat(target, str);
    }
    free(str);
}

char *String_FromDouble(double val) {
    char *str;
    int len = StringLength_Double(val);
    str = malloc(len);
    snprintf(str, len, "%f", val);
    return str;
}

void *String_Append_Double(char *target, double val, int isInitial) {
    char *str = String_FromDouble(val);
    if (isInitial == 1) {
        strcpy(target, str);
    } else {
        strcat(target, str);
    }
    free(str);
}

