#ifndef _VERTEX_H
#define _VERTEX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * File Vertex
 * digunakan untuk memanipulasi titik
 */

typedef struct {
    int x;
    int y;
} Vertex;

void scaleVertex(Vertex *v, float scale, Vertex pivot);

int isVertexCritical(Vertex a, Vertex b, Vertex c);

float vertexDistance(Vertex a, Vertex b);

#endif
