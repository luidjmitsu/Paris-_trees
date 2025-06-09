#include "../include/graph.h"

void initGraph(graph_t* graph)
{
    graph->input_file = "les-arbres.csv";
    graph->output_file = "les-arbres.bin";
    graph->source_node = 0;
    graph->nbTrees = 0;
    graph->distanceLimit = (double)MAXINT;
    graph->heightLimit = MAXINT;
}

void IsGraphEmpty(graph_t* graph)
{
    if (graph->nbTrees == 0){
        printf("The graph is empty.\n");
    } else {
        printf("The graph is not empty.\n");
    }
}