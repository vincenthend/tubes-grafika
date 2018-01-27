#ifndef _DRAWER_H
#define _DRAWER_H

#include "framebuffer.h"
#include "color.h"

void drawLine(FrameBuffer* fb, int x0, int y0, int x1, int y1, Color c);

void drawCircle(FrameBuffer* fb, int x0, int y0, int radius, Color c);

void drawSquare(FrameBuffer* fb, int x0, int y0, int x1, int y1, Color c);

#endif
