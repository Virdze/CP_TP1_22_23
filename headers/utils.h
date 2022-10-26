#ifndef UTILS_HEADER
#define UTILS_HEADER


typedef struct tuple{
    float x;
    float y;
} * Tuple;

typedef struct cluster{
    Tuple pontos;
    int nr_pontos;
    Tuple centroid; 
} * Cluster;

float euclidean_distance(Tuple p1, Tuple p2);

<<<<<<< HEAD:include/utils.h
=======
void add_point_to_cluster(Cluster c, Tuple point);
>>>>>>> 630de53185b3c463a46b729ede0dc1b9753ecef7:headers/utils.h

#endif