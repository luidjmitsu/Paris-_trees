#include "../include/makeBin.h"

int isFileExists(graph_t* graph){
    if(access(graph->output_file, F_OK) == 0) {
        return true;
    }
    return false;
}

int define_arrd(char* str){
    // string de la forme PARIS 8E ARRONDISSEMENT
    if(str == NULL || strlen(str) < 3) {
        return -1; // Invalid input
    }
    char* token = strtok(str, " ");
    if(token == NULL) {
        return -1; // No valid token found
    }
    token = strtok(NULL, " ");
    if(token == NULL) {
        return -1; // No valid token found
    }
    int arrd = atoi(token);
    if(arrd < 1 || arrd > 20) {
        return -1; // Invalid arrondissement number
    }
    return arrd;
}

double stringToDouble(char* str){
    return strtold(str, NULL);
}

void split_line(char** buffer, char** split, int n){
    char* str;
    for(int i = 0; i < n; i++) {
        str = strsep(buffer, ";");
        if(!strcmp(str, "")){
            split[i] = "VOID";
        } else {
            split[i] = strdup(str);
        }
    }
    return;
}

int get_line(FILE* f, char** line_splitted, char* buffer){
    if(fgets(buffer, SIZEOFBUFFER, f) == NULL) {
        free(buffer);
        return -1; // End of file or error
    }
    //print the line
    split_line(&buffer, line_splitted, NB_COLS);
    return 0;
}

tree_t* parse(FILE* f, graph_t* graph){
    tree_t* trees = malloc(sizeof(tree_t) * TAILLE_TAB);
    if (trees == NULL) {
        fprintf(stderr, "Memory allocation failed for trees\n");
        exit(EXIT_FAILURE);
    }
    char* line = malloc(sizeof(char*) * SIZEOFBUFFER);
    if(line == NULL) {
        fprintf(stderr, "Memory allocation failed for line\n");
        exit(EXIT_FAILURE);
    }

    char *cX, *cY;

    char** line_splitted = (char**)malloc(sizeof(char*)* NB_COLS);
    if(line_splitted == NULL) {
        fprintf(stderr, "Memory allocation failed for line_splitted\n");
        exit(EXIT_FAILURE);
    }
    int result = get_line(f, line_splitted, line);
    result = get_line(f, line_splitted, line); // Skip the header line

    int i = 0;
    while(result == 0) {
        cX = strtok(line_splitted[16], ",");
        trees[i].position.x = stringToDouble(cX);   
        cY = strtok(NULL, ",");
        trees[i].position.y = stringToDouble(cY);
        trees[i].IDBASE = atoi(line_splitted[0]);
        trees[i].arrd = define_arrd(line_splitted[3]);
        trees[i].height = atof(line_splitted[13]);
        trees[i].genre = strdup(line_splitted[8]);
        result = get_line(f, line_splitted, line);
        i++;
    }
    graph->nbTrees = i;
    printf("Total number of trees parsed: %d\n", graph->nbTrees);
    free(line_splitted); 
    return trees;
}

void writeBin(tree_t* trees, graph_t graph) {
    FILE* of = fopen(graph.output_file, "wb");
    if (of == NULL) {
        fprintf(stderr, "Error opening file %s for writing\n", graph.output_file);
        exit(EXIT_FAILURE);
    }
    fwrite(&graph.nbTrees, sizeof(int), 1, of);
    for (int i = 0; i < graph.nbTrees; i++) {
        fwrite(&trees[i], sizeof(tree_t), 1, of);
    }
    fclose(of);
    printf("Data saved to binary file %s\n", graph.output_file);
    free(trees);
}

void minMax(tree_t tree, coord_t* min, coord_t* max){
    if(tree.position.x > max->x) {
        max->x = tree.position.x;
    } else if(tree.position.x < min->x){
        min->x = tree.position.x;
    } else if (tree.position.y > max->y) {
        max->y = tree.position.y;
    } else if(tree.position.y < min->y){
        min->y = tree.position.y;
    } 
}

tree_t* readBin(graph_t* graph)
{
    coord_t min = {INFINITY, INFINITY}, max = {0,0};
    FILE* f = fopen(graph->output_file, "rb");
    if (f == NULL) {
        fprintf(stderr, "Error opening file %s for writing\n", graph->output_file);
        exit(EXIT_FAILURE);
    }
    fread(&graph->nbTrees, sizeof(int), 1, f);
    tree_t* trees = malloc(sizeof(tree_t) * graph->nbTrees);
    if (trees == NULL) {
        fprintf(stderr, "Memory allocation failed for trees\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < graph->nbTrees; i++) {
        fread(&trees[i], sizeof(tree_t), 1, f);
        addCoord(&graph->graphScale.moyenne, &trees[i].position);
        minMax(trees[i], &min, &max);
    }
    fclose(f);
    graph->graphScale.facteur.x = graph->graphScale.lenght / (max.x - min.x);
    graph->graphScale.facteur.y = graph->graphScale.width / (max.y - min.y);
    multiplyCoord(&graph->graphScale.moyenne, 1.0/graph->nbTrees);
    return trees;
}