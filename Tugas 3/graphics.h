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
    Shape *dict[256];
    int height;
    int width;
} RasterFont;

void openFont(char *font, Font *f);

void openImage(char *image, Image *i);

void openRasterFont(char *raster_font, RasterFont *f);

#endif
