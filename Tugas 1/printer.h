#ifndef _PRINTER_H
#define _PRINTER_H

#include "framebuffer.h"
#include "color.h"
#include "font.h"

extern char* cdict[255];

void printChar(FrameBuffer* fb, char c, Font f, int x, int y, Color col);

void printString(FrameBuffer* fb, char* s, Font f, int x, int y, Color col);

#endif
