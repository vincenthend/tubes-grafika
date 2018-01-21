#ifndef _PRINTER_H
#define _PRINTER_H

#include "framebuffer.h"

extern char* cdict[255];

void initializeDictionary();

void bufferChar(FrameBuffer* fb, char c, int char_width, int char_height, int x, int y, int scale, int r, int g, int b, int a);

void bufferString(FrameBuffer* fb, char* s, int char_width, int char_height, int x, int y, int spacing, int scale, int r, int g, int b, int a);

void alignString(FrameBuffer* fb, char* c, int char_width, int char_height, int alignment, int y, int spacing, int scale, int r, int g, int b, int a);

#endif
