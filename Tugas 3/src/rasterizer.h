#ifndef _RASTERIZER_H
#define _RASTERIZER_H

#include "drawer.h"
#include "graphics/rasterfont.h"
#include "graphics/shape.h"

#define MAX_VERTICES 25

void boundaryFill(FrameBuffer *fb, int x, int y, Color c);

void scanlineFill(FrameBuffer *fb, Shape *s, Color c, int arr[]);

void fillShape(FrameBuffer *fb, Shape *s, Color color, char c);

void fillChar(FrameBuffer *fb, char ch, RasterFont *rasterFont, Vertex offset, Color c);

void fillString(FrameBuffer *fb, char *s, RasterFont *rasterFont, Vertex offset,
                Color c);

void fillSquareArea(FrameBuffer *fb, int x0, int y0, int x1, int y1, Color c);

void fillRainbow(FrameBuffer *fb, int x, int y);

#endif
