#include "drawer.h"

#include <math.h>

void swap(int* a, int* b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void drawLine(FrameBuffer* fb, int x0, int y0, int x1, int y1, Color c) {
    char steep = abs(y1 - y0) > abs(x1 - x0);

    // Check if the line is steep (m>1)
    // Swap x and y if true
    if (steep) {
        swap(&x0, &y0);
        swap(&x1, &y1);
    }

    // Check if the line grows from right to left,
    // swap start and end points if true.
    if (x0 > x1) {
        swap(&x0, &x1);
        swap(&y0, &y1);
    }

    int dx = x1 - x0;
    int dy = abs(y1 - y0);
    int error = dx / 2;
    int ystep;
    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    int x;
    int y = y0;
    for (x = x0; x <= x1; x++) {
        if (steep) {
            addPixelToBuffer(fb, y, x, c.r, c.g, c.b, c.a);
        } else {
            addPixelToBuffer(fb, x, y, c.r, c.g, c.b, c.a);
        }

        error -= dy;

        if (error < 0) {
            y += ystep;
            error += dx;
        }
    }
}

void drawThickLine(FrameBuffer *fb, int x0, int y0, int x1, int y1, int width, Color c) {
    char steep = abs(y1 - y0) > abs(x1 - x0);

    // Check if the line is steep (m>1)
    // Swap x and y if true
    if (steep) {
        swap(&x0, &y0);
        swap(&x1, &y1);
    }

    // Check if the line grows from right to left,
    // swap start and end points if true.
    if (x0 > x1) {
        swap(&x0, &x1);
        swap(&y0, &y1);
    }

    int dx = x1 - x0;
    int dy = abs(y1 - y0);
    int error = dx / 2;
    int ystep;
    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    int x;
    int y = y0;
    for (x = x0; x <= x1; x++) {
        if (steep) {
            drawFilledCircle(fb, y, x, width, c);
        } else {
            drawFilledCircle(fb, x, y, width, c);
        }

        error -= dy;

        if (error < 0) {
            y += ystep;
            error += dx;
        }
    }
}

void drawCircle(FrameBuffer* fb, int x0, int y0, int radius, Color c) {
    int x = radius;
    int y = 0;
    int radiusError = 1 - x;

    while (x >= y) {
        addPixelToBuffer(fb, x + x0, y + y0, c.r, c.g, c.b, c.a);
        addPixelToBuffer(fb, y + x0, x + y0, c.r, c.g, c.b, c.a);
        addPixelToBuffer(fb, -x + x0, y + y0, c.r, c.g, c.b, c.a);
        addPixelToBuffer(fb, -y + x0, x + y0, c.r, c.g, c.b, c.a);
        addPixelToBuffer(fb, -x + x0, -y + y0, c.r, c.g, c.b, c.a);
        addPixelToBuffer(fb, -y + x0, -x + y0, c.r, c.g, c.b, c.a);
        addPixelToBuffer(fb, x + x0, -y + y0, c.r, c.g, c.b, c.a);
        addPixelToBuffer(fb, y + x0, -x + y0, c.r, c.g, c.b, c.a);

        y++;

        if (radiusError < 0) {
            radiusError += 2 * y + 1;
        } else {
            x--;
            radiusError += 2 * (y - x + 1);
        }
    }
}

void drawFilledCircle(FrameBuffer* fb, int x0, int y0, int radius, Color c) {
    int current_radius;

    for (current_radius=1; current_radius<=radius; current_radius++) {
        int x = radius;
        int y = 0;
        int radiusError = 1 - x;

        while (x >= y) {
            addPixelToBuffer(fb, x + x0, y + y0, c.r, c.g, c.b, c.a);
            addPixelToBuffer(fb, y + x0, x + y0, c.r, c.g, c.b, c.a);
            addPixelToBuffer(fb, -x + x0, y + y0, c.r, c.g, c.b, c.a);
            addPixelToBuffer(fb, -y + x0, x + y0, c.r, c.g, c.b, c.a);
            addPixelToBuffer(fb, -x + x0, -y + y0, c.r, c.g, c.b, c.a);
            addPixelToBuffer(fb, -y + x0, -x + y0, c.r, c.g, c.b, c.a);
            addPixelToBuffer(fb, x + x0, -y + y0, c.r, c.g, c.b, c.a);
            addPixelToBuffer(fb, y + x0, -x + y0, c.r, c.g, c.b, c.a);

            y++;

            if (radiusError < 0) {
                radiusError += 2 * y + 1;
            } else {
                x--;
                radiusError += 2 * (y - x + 1);
            }
        }    
    }
}

void drawSquare(FrameBuffer* fb, int x0, int y0, int x1, int y1, Color c){
    drawLine(fb, x0, y0, x0, y1, c);
    drawLine(fb, x0, y1, x1, y1, c);
    drawLine(fb, x1, y1, x1, y0, c);
    drawLine(fb, x1, y0, x0, y0, c);
}

void drawMonoImage(FrameBuffer* fb, Image img, int x, int y, Color col){
    int i, j;
    char* data = img.data;
    for (i = 0; i < img.height; i++) {
        for (j = 0; j < img.width; j++) {
            if (data[i * img.width + j] == '1') {
                addPixelToBuffer(fb, (x) + j, (y) + i, col.r, col.g, col.b,
                                 col.a);
            }
        }
    }
}

void fillSquareArea(FrameBuffer* fb, int x0, int y0, int x1, int y1, Color c){
    int x, y;
    for(x=x0; x<=x1; x++){
        for(y=y0; y<=y1; y++){
            addPixelToBuffer(fb, x, y, c.r, c.g, c.b, c.a);
        }
    }
}