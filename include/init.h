#ifndef __INIT_H
#define __INIT_H

enum BOOL {FALSE, TRUE};

void *getPrintInteger(int val);
void *getPrintDouble(double val);
void *getPrintString(char *val);
int getStringLengthInteger(int val);
int getStringLengthString(char *str);
int getStringLengthDouble(double val);
char *getStringFromInteger(int val);
void *getStringAppendInteger(char *target, int val, int isInitial);
char *getStringFromDouble(double val);
void *getStringAppendDouble(char *target, double val, int isInitial);

#endif