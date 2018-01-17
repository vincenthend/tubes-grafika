#ifndef _FRAMEBUFFER_H
#define _FRAMEBUFFER_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

typedef struct {
    int fbfd;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    int width;
    int height;
    int depth;
    int screensize;
    char* buffer;
} FrameBuffer;


/**
 * Menginisialisasi objek frame buffer
 **/
FrameBuffer initFB();

/**
 * Mencetak pada posisi x dan y tertentu
 **/
void printPixel(FrameBuffer* buffer, int x, int y, int r, int g, int b, int a);

/**
 * Menyimpan perubahan pada layar
 **/
void finalizeChanges(FrameBuffer* buff);


#endif
