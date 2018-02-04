#ifndef _RASTERIZER_H
#define _RASTERIZER_H

#include "color.h"
#include "framebuffer.h"

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

typedef struct {
    Shape *dict[256];
    int height;
    int width;
} RasterFont;

void initPolygon(Polygon *p, int n);

void initShape(Shape *s, int n);

void drawPolygon(FrameBuffer *fb, const Polygon *p, Color c);

void fillShape(FrameBuffer *fb, Shape *s, Color c);

int findMinXInShape(Polygon *polygons, int polygon_count);

int findMaxXInShape(Polygon *polygons, int polygon_count);

int findMinYInShape(Polygon *polygons, int polygon_count);

int findMaxYInShape(Polygon *polygons, int polygon_count);

int findMinXInPolygon(Vertex *vertices, int vertex_count);

int findMaxXInPolygon(Vertex *vertices, int vertex_count);

int findMinYInPolygon(Vertex *vertices, int vertex_count);

int findMaxYInPolygon(Vertex *vertices, int vertex_count);

void fillChar(FrameBuffer *fb, char ch, RasterFont *rf, Vertex offset, Color c);

void fillString(FrameBuffer *fb, char *s, RasterFont *rf, Vertex offset, Color c);

#endif
