#ifndef _DRAWER_H
#define _DRAWER_H

#include <math.h>

#include "color.h"
#include "framebuffer.h"
#include "graphics.h"

void drawLine(FrameBuffer *fb, int x0, int y0, int x1, int y1, Color c);

void drawThickLine(FrameBuffer *fb, int x0, int y0, int x1, int y1, int width,
                   Color c);

void drawCircle(FrameBuffer *fb, int x0, int y0, int radius, Color c);

void drawFilledCircle(FrameBuffer *fb, int x0, int y0, int radius, Color c);

void drawSquare(FrameBuffer *fb, int x0, int y0, int x1, int y1, Color c);

void drawMonoImage(FrameBuffer *fb, Image image, int x, int y, Color col);

void drawNyanImage(FrameBuffer *fb, Image image, int x, int y, Color lineColor,
                   Color clothColor, Color skinColor);

void fillSquareArea(FrameBuffer *fb, int x0, int y0, int x1, int y1, Color c);

#endif
