#pragma once

typedef struct coord
{
    double x,y;
} coord_t;

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
    tree_t* trees;
    double distanceLimit;
    int heightLimit;
} graph_t;