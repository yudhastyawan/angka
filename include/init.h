#ifndef __INIT_H
#define __INIT_H

enum BOOL {FALSE, TRUE};

void *Integer_Print(int val);
void *Double_Print(double val);
int StringLength_Integer(int val);
int StringLength_String(char *str);
int StringLength_Double(double val);
char *String_FromInteger(int val);
void *String_Append_Integer(char *target, int val, int isInitial);
char *String_FromDouble(double val);
void *String_Append_Double(char *target, double val, int isInitial);

#endif