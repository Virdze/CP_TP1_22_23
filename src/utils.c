#include "../include/utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float euclidean_distance(Tuple p1, Tuple p2){
    float result = sqrtf(powf(p2->x - p1->y, 2) + powf(p2->y - p1->y,2));
    return result;
}



