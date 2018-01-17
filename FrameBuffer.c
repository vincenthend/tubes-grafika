#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "FrameBuffer.h"


/**
 * Menginisialisasi objek frame buffer
 **/
FrameBuffer initFB(){
    FrameBuffer fb;
    fb.fbfd = open("/dev/fb0", O_RDWR);
    if(fb.fbfd == -1){
        //Fail
        printf("Error, have you run it as admin?\n");
    }
    
    if(ioctl(fb.fbfd, FBIOGET_FSCREENINFO, &fb.finfo) == -1){
        //Error
        printf("Error getting fixed info\n");
    }
    if(ioctl(fb.fbfd, FBIOGET_VSCREENINFO,&fb.vinfo) == -1){
        //Error 
        printf("Error getting variable info\n");
    }
    
    fb.width = fb.vinfo.xres;
    fb.height = fb.vinfo.yres;
    fb.depth = fb.vinfo.bits_per_pixel;
    fb.screensize = fb.width * fb.height * fb.depth / 8;
    fb.buffer = (char *) mmap(0, fb.screensize,PROT_READ | PROT_WRITE, MAP_SHARED, fb.fbfd, 0);
    if((int)fb.buffer == -1){
        //Error
        printf("Error reading buffer\n");
    }

    printf("Screensize %dx%d\n", fb.width, fb.height);
    return fb;
}

void printPixel(FrameBuffer* buffer, int x, int y, int r, int g, int b, int a){
    char* buff = buffer->buffer;
    int location =  (x + buffer->vinfo.xoffset) * (buffer->vinfo.bits_per_pixel/8) +
                    (y + buffer->vinfo.yoffset) * (buffer->finfo.line_length);

    if(buffer->vinfo.bits_per_pixel == 32) {
        *(buff + location) = b;
        *(buff + location + 1) = g;
        *(buff + location + 2) = r;
        *(buff + location + 3) = a;
    }
    else {
        printf("depth err");
    }
}

void finalizeChanges(FrameBuffer* buff){
    munmap(buff->buffer, buff->screensize);
    close(buff->fbfd);
    printf("Job's done~!\n");
}
