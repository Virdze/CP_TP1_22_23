#include "../include/utilsv2.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

inline float euclidean_distance(Tuple p1, Tuple p2){
    return sqrt((p2.y - p1.y)*(p2.y - p1.y) + (p2.x - p1.x) * (p2.x - p1.x));
}




