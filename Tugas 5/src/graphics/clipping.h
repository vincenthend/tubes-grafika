#ifndef _CLIPPING_H
#define _CLIPPING_H

#include "vectorimage.h"

typedef struct {
    Vertex *clipperVertex;
    int clipperSize;
} Clipper;

void initSquareClipper(Clipper *clipper, int x0, int y0, int x1, int y1);

int countVertexInsideClip(Polygon *polygon, Vertex clip1, Vertex clip2);

int countPolygonInsideClip(Shape *shapes, Vertex clip1, Vertex clip2);

int countShapeInsideClip(VectorImage *image, Vertex clip1, Vertex clip2);

void clipVectorImageHelper(VectorImage *image, Vertex clip1, Vertex clip2);

void clipVectorImage(VectorImage *image, Clipper clipper);

Vertex findIntersect(Vertex line1, Vertex line2, Vertex line3, Vertex line4);

#endif
