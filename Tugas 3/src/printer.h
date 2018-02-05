#ifndef _PRINTER_H
#define _PRINTER_H

#include "color.h"
#include "framebuffer.h"
#include "graphics/font.h"

void printChar(FrameBuffer *fb, char c, Font f, int x, int y, Color col);

void printString(FrameBuffer *fb, char *s, Font f, int x, int y, Color col);

#endif
