#ifndef _FRAMEBUFFER_H
#define _FRAMEBUFFER_H

#include <fcntl.h>
#include <linux/fb.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "color.h"

typedef struct {
    int fbfd;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    int screen_width;
    int screen_height;
    int screen_density;
    int screen_size;
    char *buffer;
} FrameBuffer;

FrameBuffer initFrameBuffer();

void addPixelToBuffer(FrameBuffer *fb, int x, int y, int r, int g, int b,
                      int a);

void updateFrame(FrameBuffer *fb);

Color getColor(const FrameBuffer *fb, int x, int y);

#endif
