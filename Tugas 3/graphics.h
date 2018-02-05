#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *dict[256];
    int height;
    int width;
} Font;

typedef struct {
    char *data;
    int height;
    int width;
} Image;

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
    Shape *dict;
    int height;
    int width;
} RasterFont;

void openFont(char *font, Font *f);

void openImage(char *image, Image *i);

void openRasterFont(char *raster_font, RasterFont *f);

#endif
