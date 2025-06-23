#include "../include/graph.h"
#include "../include/makeBin.h"

void initGraph(graph_t* graph)
{
    graph->input_file = INPUT_FILE;
    graph->output_file = OUTPUT_FILE;
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

void drawMap(graph_t* graph){
    if (graph == NULL || graph->nbTrees == 0) {
        fprintf(stderr, "Graph or trees are not initialized.\n");
        return;
    }
    tree_t* trees = readBin(graph);
    tps_createWindow("Les arbres de Paris", 800, 600);
    while(tps_isRunning()) {
        tps_background(255, 255, 255);
        tps_setColor(0, 0, 0);
        for (int i = 0; i < graph->nbTrees; i++) {
            tps_fillEllipse(trees[i].position.x, trees[i].position.y, 0.8, 0.8);
        }
        tps_render();
    }
    tps_closeWindow();
    free(trees);
}