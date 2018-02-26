#ifndef _SHAPE_H
#define _SHAPE_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "polygon.h"
#include "vertex.h"

/**
 * File Shape
 * digunakan untuk memanipulasi bentuk
 */

typedef struct {
    Polygon *polygons;
    int polygonCount;
    Vertex upperLeft;
    Vertex lowerRight;
    Vertex center;
} Shape;

void initShape(Shape *shape, int polygonCount);

void cloneShape(const Shape *src, Shape *dest);

void destroyShape(Shape *shape);

void offsetShape(Shape *shape, const Vertex vertex);

void normalizeShapeOffset(Shape *shape, const Vertex vertex);

void scaleVertex(Vertex *v, float scale, Vertex pivot);

void scaleShape(Shape *shape, float scale, Vertex pivot);

void calculateShapeBoundaries(Shape *shape);

void calculateShapeCenter(Shape *shape);

void prepareShapeForRotation(Shape *shape, Vertex pivot);

void rotateShape(Shape *shape, const int degrees, Vertex pivot);

#endif
