#ifndef UTILSV2_HEADER
#define UTILSV2_HEADER


typedef struct tuple{
    float x;
    float y;
    int cluster;
} Tuple;

typedef struct cluster{
    int nr_pontos;
    Tuple centroid; 
} Cluster;

float euclidean_distance(Tuple p1, Tuple p2);


#endif