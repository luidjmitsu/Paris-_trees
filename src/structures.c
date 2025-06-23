#include "structures.h"

void addCoord(coord_t* c1, coord_t* c2) 
{
    c1->x += c2->x;
    c1->y += c2->y;
}

void multiplyCoord(coord_t* c1, double factor){
    c1->x *= factor;
    c1->y *= factor;
}
