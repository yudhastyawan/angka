#include <stdlib.h>
#include <time.h>
#include "standard.h"

double Random(double min, double max)
{
    static int check_random = 0;
    if (check_random == 0){
        srand(time(0));
    }
    double range = (max - min); 
    double div = RAND_MAX / range;
    check_random++;
    return min + (rand() / div);
}

void Data_Delete(void *__ptr) {
    free(__ptr);
}
