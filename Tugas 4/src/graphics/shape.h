#ifndef _SHAPE_H
#define _SHAPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int y;
} Vertex;

typedef struct {
    Vertex *vertices;
    int vertexCount;
} Polygon;

typedef struct {
    Polygon *polygons;
    int polygonCount;
    Vertex upperLeft;
    Vertex lowerRight;
    Vertex center;
} Shape;

void initPolygon(Polygon *polygon, int vertexCount);

void initShape(Shape *shape, int polygonCount);

void cloneShape(const Shape* src, Shape* dest);

void destroyShape(Shape *shape);

void offsetShape(Shape *shape, const Vertex vertex);

void normalizeShapeOffset(Shape *shape, const Vertex vertex);

void growShape(Shape *shape, int multiplierScale);

void shrinkShape(Shape *shape, int dividerScale);

void calculateBoundaries(Shape *shape);

void prepareShapeForRotation(Shape *shape);

void rotateShape(Shape *shape, const int degrees);

int isCritical(Vertex a, Vertex b, Vertex c);

float distance(Vertex a, Vertex b);

#endif
