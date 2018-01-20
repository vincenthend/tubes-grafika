#include "framebuffer.h"

FrameBuffer initialize() {
    FrameBuffer fb;

    fb.fbfd = open("/dev/fb0", O_RDWR);
    if (fb.fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }

    if (ioctl(fb.fbfd, FBIOGET_FSCREENINFO, &fb.finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    if (ioctl(fb.fbfd, FBIOGET_VSCREENINFO, &fb.vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }


    fb.screen_width = fb.vinfo.xres;
    fb.screen_height = fb.vinfo.yres;
    fb.screen_density = fb.vinfo.bits_per_pixel;
    fb.screen_size = fb.screen_width * fb.screen_height * fb.screen_density / 8;
    
    fb.buffer = (char *)mmap(0, fb.screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, fb.fbfd, 0);
    if ((int)fb.buffer == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }

    return fb;
}

void addPixelToBuffer(FrameBuffer* fb, int x, int y, int r, int g, int b, int a) {
    char* buffer = fb->buffer;
    long int location = (x+fb->vinfo.xoffset) * (fb->vinfo.bits_per_pixel/8) +
                        (y+fb->vinfo.yoffset) * (fb->finfo.line_length);

    if (fb->screen_density == 32) {
        *(buffer + location) = b;
        *(buffer + location + 1) = g;
        *(buffer + location + 2) = r;
        *(buffer + location + 3) = a;
    } else  { //assume 16bpp
        exit(3);
    }
}

void updateFrame(FrameBuffer* fb) {
    munmap(fb->buffer, fb->screen_size);
    close(fb->fbfd);
    printf("Frame updated\n");
}

void setBackground(FrameBuffer* fb, int r, int g, int b, int a) {
    int i, j;
    for (i = 0; i < fb->screen_width; i++) {
        for (j=0; j< fb->screen_height; j++) {
            addPixelToBuffer(fb, i, j, r, g, b, a);
        }
    }
}

void clearScreen(FrameBuffer* fb) {
    int i, j;
    for (i = 0; i < fb->screen_width; i++) {
        for (j=0; j< fb->screen_height; j++) {
            addPixelToBuffer(fb, i, j, 0, 0, 0, 0);
        }
    }
}