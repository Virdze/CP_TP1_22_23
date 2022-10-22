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

void add_point_to_cluster(Cluster c, Tuple point);

#endif