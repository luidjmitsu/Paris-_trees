#include "../include/structures.h"
#include "../include/makeBin.h"
#include "../include/graph.h"

int main(void){
    graph_t graph;
    initGraph(&graph);
    
    if(!isFileExists(&graph)) {
        FILE* f = fopen(graph.input_file, "r");
        if (f == NULL) {
            fprintf(stderr, "Error opening file %s\n", graph.input_file);
            return 1;
        }
        tree_t* trees = parse(f, &graph);
        fclose(f);

        writeBin(trees, graph);
    }
    drawMap(&graph);

    return 0;
}