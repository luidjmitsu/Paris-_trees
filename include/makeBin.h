#include "library.h"
#include "graph.h"
#include "unistd.h"

tree_t* parse(FILE* f, graph_t* graph);
int get_line(FILE* f, char** line_splitted, char* buffer);
int isFileExists(graph_t* graph);
void split_line(char** line, char** split, int n);
void saveToBin(tree_t* trees, graph_t graph);
double stringToDouble(char* str);
void writeBin(tree_t* trees, graph_t graph);
tree_t* readBin(graph_t* graph);