#include "init.h"
#include "standard.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

double agx_random(double min, double max)
{
    static int check_random = 0;
    double tmp1, tmp2, res;
    if (check_random == 0){
        srand(time(NULL));
    }
    tmp1 = (max - min); 
    tmp2 = RAND_MAX / tmp1;
    check_random++;
    tmp1 = rand() / tmp2;
    res = min + tmp1;
    return res;
}

void agx_data_delete(void *__ptr) {
    free(__ptr);
    __ptr = NULL;
}

