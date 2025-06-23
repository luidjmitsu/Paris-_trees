#pragma once

typedef struct coord
{
    double x,y;
} coord_t;

typedef struct parameters
{
    coord_t moyenne, facteur;
    int lenght, width;
} parameters_t;

typedef struct tree
{
    int IDBASE, height, arrd;
    char* genre;
    coord_t position;
} tree_t;

typedef struct graph 
{
    char* input_file, *output_file;
    int source_node;
    int nbTrees;
    double distanceLimit;
    int heightLimit;
    parameters_t graphScale;
} graph_t;

void addCoord(coord_t* c1, coord_t* c2);

void multiplyCoord(coord_t* c1, double factor);