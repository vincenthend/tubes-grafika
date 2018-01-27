#ifndef _DRAWER_H
#define _DRAWER_H

#include "framebuffer.h"
#include "color.h"
#include "graphics.h"

void drawLine(FrameBuffer* fb, int x0, int y0, int x1, int y1, Color c);

void drawCircle(FrameBuffer* fb, int x0, int y0, int radius, Color c);

void drawSquare(FrameBuffer* fb, int x0, int y0, int x1, int y1, Color c);

void drawMonoImage(FrameBuffer* fb, Image img, int x, int y, Color col);

void fillSquareArea(FrameBuffer* fb, int x0, int y0, int x1, int y1, Color c);
#endif
