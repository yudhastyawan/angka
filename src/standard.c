#include "init.h"
#include "standard.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

double agx_random(double min, double max)
{
    static int check_random = 0;
    if (check_random == 0){
        srand(time(NULL));
    }
    double range = (max - min); 
    double div = RAND_MAX / range;
    check_random++;
    double res = min + (rand() / div);
    return res;
}

void agx_data_delete(void *__ptr) {
    free(__ptr);
}

