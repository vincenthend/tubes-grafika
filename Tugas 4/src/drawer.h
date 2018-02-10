#ifndef _DRAWER_H
#define _DRAWER_H

#include <math.h>

#include "color.h"
#include "framebuffer.h"
#include "graphics/image.h"
#include "graphics/shape.h"

/**
 * File Drawer
 * Digunakan untuk menggambar garis/lingkaran/bidang lainnya/gambar
 */

void drawLine(FrameBuffer *fb, int x0, int y0, int x1, int y1, Color color);

void drawThickLine(FrameBuffer *fb, int x0, int y0, int x1, int y1, int width,
                   Color color);

void drawCircle(FrameBuffer *fb, int x0, int y0, int radius, Color color);

void drawFilledCircle(FrameBuffer *fb, int x0, int y0, int radius, Color color);

void drawSquare(FrameBuffer *fb, int x0, int y0, int x1, int y1, Color color);

void drawMonoImage(FrameBuffer *fb, Image image, int x, int y, Color color);

void drawNyanImage(FrameBuffer *fb, Image image, int x, int y, Color lineColor,
                   Color clothColor, Color skinColor);

void drawPolygon(FrameBuffer *fb, const Polygon *polygon, Color color);

#endif
