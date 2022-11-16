#include "../include/utilsv2.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int verify_centroids(Tuple t1, Tuple t2){
    return (t1.x == t2.x && t1.y == t2.y);
}
