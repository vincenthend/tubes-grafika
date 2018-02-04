#ifndef _DRAWER_H
#define _DRAWER_H

#include "framebuffer.h"

void drawLine(FrameBuffer *fb, int x0, int y0, int x1, int y1, int r, int g,
              int b, int a);

void drawCircle(FrameBuffer *fb, int x0, int y0, int radius, int r, int g,
                int b, int a);

#endif
