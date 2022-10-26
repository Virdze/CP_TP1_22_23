#include "../include/utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float euclidean_distance(Tuple p1, Tuple p2){
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y,2));
}




