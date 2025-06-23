#include "../include/graph.h"
#include "../include/makeBin.h"

void initGraphParameters(parameters_t* parameters){
    parameters->moyenne.x = 0;
    parameters->moyenne.y = 0;
    parameters->facteur.x = 0;
    parameters->facteur.y = 0;
    parameters->lenght = 1900;
    parameters->width = 900;
}

void initGraph(graph_t* graph)
{
    graph->input_file = INPUT_FILE;
    graph->output_file = OUTPUT_FILE;
    graph->source_node = 0;
    graph->nbTrees = 0;
    graph->distanceLimit = (double)MAXINT;
    graph->heightLimit = MAXINT;
    initGraphParameters(&graph->graphScale);
}

void IsGraphEmpty(graph_t* graph)
{
    if (graph->nbTrees == 0){
        printf("The graph is empty.\n");
    } else {
        printf("The graph is not empty.\n");
    }
}

void drawTree(graph_t* graph, tree_t tree, double size){
    tps_fillEllipse(graph->graphScale.lenght/2 + (graph->graphScale.moyenne.x - tree.position.x) * graph->graphScale.facteur.x,
             graph->graphScale.width/2 + (graph->graphScale.moyenne.y - tree.position.y) * graph->graphScale.facteur.y, size, size);
}

void drawMap(graph_t* graph, double size){
    tree_t* trees = readBin(graph);
    if (graph == NULL || graph->nbTrees == 0) {
        free(trees);
        fprintf(stderr, "Graph or trees are not initialized.\n");
        return;
    }
    tps_createWindow("Les arbres de Paris", graph->graphScale.lenght, graph->graphScale.width);
    while(tps_isRunning()) {
        tps_background(255, 255, 255);
        tps_setColor(0, 0, 0);
        for (int i = 0; i < graph->nbTrees; i++) {
            drawTree(graph, trees[i], size);
        }
        tps_fillEllipse(0,0,10,10);
        tps_render();
    }
    tps_closeWindow();
    free(trees);
}