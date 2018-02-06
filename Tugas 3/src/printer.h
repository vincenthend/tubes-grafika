#ifndef _PRINTER_H
#define _PRINTER_H

#include "color.h"
#include "framebuffer.h"
#include "graphics/font.h"

void printChar(FrameBuffer *fb, char c, Font font, int x, int y, Color color);

void printString(FrameBuffer *fb, char *s, Font font, int x, int y,
                 Color color);

#endif
