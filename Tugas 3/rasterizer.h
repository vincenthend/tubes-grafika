#ifndef _RASTERIZER_H
#define _RASTERIZER_H

#include "color.h"
#include "drawer.h"
#include "framebuffer.h"
#include "graphics.h"

#define MAX_VERTICES 25

typedef struct {
    int x;
    int y;
} Vertex;

typedef struct {
    Vertex *vertices;
    int count;
} Polygon;

typedef struct {
    Polygon *polygons;
    int count;
} Shape;

void initPolygon(Polygon *p, int n);

void initShape(Shape *s, int n);

void drawPolygon(FrameBuffer *fb, const Polygon *p, Color c);

/**
 * A simple polygon is a polygon without any intersecting sides.
 */
void fillShape(FrameBuffer *fb, Shape *s, Color c);

#endif
