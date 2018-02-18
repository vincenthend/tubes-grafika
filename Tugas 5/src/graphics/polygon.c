#include "polygon.h"

void initPolygon(Polygon *polygon, int vertexCount) {
    polygon->vertices = (Vertex *)malloc(vertexCount * sizeof(Vertex));
    polygon->vertexCount = vertexCount;
}

void clonePolygon(const Polygon *src, Polygon *dest) {
    dest->vertexCount = src->vertexCount;
    dest->vertices = (Vertex *)malloc(dest->vertexCount * sizeof(Vertex));
    for (int i = 0; i < dest->vertexCount; i++) {
        dest->vertices[i].x = src->vertices[i].x;
        dest->vertices[i].y = src->vertices[i].y;
    }
}
