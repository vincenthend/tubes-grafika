#ifndef _RASTERIZER_H
#define _RASTERIZER_H

#include "drawer.h"
#include "graphics/rasterfont.h"
#include "graphics/shape.h"
#include "graphics/vectorimage.h"

/**
 * File Rasterizer
 * Digunakan untuk melakukan fill (pewarnaan)
 */

void floodFill(FrameBuffer *fb, int x, int y, Vertex topLeft, Vertex bottomRight, Color color);

void floodFill_recursive(FrameBuffer *fb, int x, int y, Vertex topLeft, Vertex bottomRight, Color color);

void boundaryFill(FrameBuffer *fb, Shape *s, Color color);

void scanlineFill(FrameBuffer *fb, Shape *s, Color color);

void fillShape(FrameBuffer *fb, Shape *s, Color color);

void fillChar(FrameBuffer *fb, char c, RasterFont *rf, Vertex offset,
              Color color);

void fillString(FrameBuffer *fb, char *s, RasterFont *rf, Vertex offset,
                Color color);

void fillSquareArea(FrameBuffer *fb, int x0, int y0, int x1, int y1,
                    Color color);

void fillRainbow(FrameBuffer *fb, int x, int y);

void fillImage(FrameBuffer *fb, VectorImage *image, Vertex offset);

void clearArea(FrameBuffer *fb, Vertex v0, Vertex v1);

#endif
