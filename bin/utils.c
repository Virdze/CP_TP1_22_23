#include "utils.h"

#include <stdio.h>
#include <stdlib.h>


void add_point_to_cluster(Cluster c, Tuple point){
    
    if(!c.pontos){
        c.pontos = (Tuple *) malloc(sizeof(struct tuple));
        c.pontos[0] = point;
        c.nr_pontos++;
    }
    else{
        c.pontos[c.nr_pontos] = point;
        c.nr_pontos++;
    }
}
