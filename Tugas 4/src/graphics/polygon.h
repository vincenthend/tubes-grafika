#ifndef _POLYGON_H
#define _POLYGON_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vertex.h"

/**
 * File Polygon
 * digunakan untuk memanipulasi poligon
 */

typedef struct {
    Vertex *vertices;
    int vertexCount;
} Polygon;

void initPolygon(Polygon *polygon, int vertexCount);

#endif
