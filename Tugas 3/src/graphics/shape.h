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
} Shape;

void initPolygon(Polygon *polygon, int vertexCount);

void initShape(Shape *shape, int polygonCount);

void offsetShape(Shape *shape, const Vertex vertex);

int findMinXInPolygon(Vertex *vertices, int vertexCount);

int findMaxXInPolygon(Vertex *vertices, int vertexCount);

int findMinYInPolygon(Vertex *vertices, int vertexCount);

int findMaxYInPolygon(Vertex *vertices, int vertexCount);

int findMinXInShape(Polygon *polygons, int polygonCount);

int findMaxXInShape(Polygon *polygons, int polygonCount);

int findMinYInShape(Polygon *polygons, int polygonCount);

int findMaxYInShape(Polygon *polygons, int polygonCount);

#endif
