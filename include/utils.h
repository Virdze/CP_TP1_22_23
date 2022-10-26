#ifndef UTILS_HEADER
#define UTILS_HEADER


typedef struct tuple{
    float x;
    float y;
} Tuple;

typedef struct cluster{
    Tuple * pontos;
    int nr_pontos;
    Tuple centroid; 
} Cluster;

float euclidean_distance(Tuple p1, Tuple p2);


#endif