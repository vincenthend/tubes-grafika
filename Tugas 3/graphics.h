#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rasterizer.h"

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

void openFont(char *fontChar, Font *font);

void openImage(char *imageName, Image *image);

void openRasterFont(char *rasterFontChar, RasterFont *rasterFont);

#endif
