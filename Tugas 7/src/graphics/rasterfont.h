#ifndef _RASTERFONT_H
#define _RASTERFONT_H

#include "shape.h"

/**
 * File RasterFont
 * digunakan untuk memanipulasi huruf raster
 */

typedef struct {
    Shape *dict;
    int height;
    int width;
} RasterFont;

void initRasterFont(RasterFont *rf);

void openRasterFont(char *ch, RasterFont *rf);

#endif
