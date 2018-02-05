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

void initPolygon(Polygon *p, int n);

void initShape(Shape *s, int n);

void offsetShape(Shape *s, const Vertex v);

int findMinXInPolygon(Vertex *vertices, int vertex_count);

int findMaxXInPolygon(Vertex *vertices, int vertex_count);

int findMinYInPolygon(Vertex *vertices, int vertex_count);

int findMaxYInPolygon(Vertex *vertices, int vertex_count);

int findMinXInShape(Polygon *polygons, int polygon_count);

int findMaxXInShape(Polygon *polygons, int polygon_count);

int findMinYInShape(Polygon *polygons, int polygon_count);

int findMaxYInShape(Polygon *polygons, int polygon_count);

#endif
