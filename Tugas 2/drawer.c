#include "drawer.h"

void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void drawLine(FrameBuffer* fb, int x0, int y0, int x1, int y1, int r, int g, int b, int a) {
    char steep = abs(y1-y0) > abs(x1-x0);
    
    int temp;

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

    int dx = x1-x0;
    int dy = abs(y1-y0);
    int error = dx/2;
    int ystep;
    if (y0 < y1) {
        ystep = 1;
    }
    else {
        ystep = -1;
    }

    int x;
    int y = y0;
    for (x=x0; x<=x1; x++) {
        if (steep) {
            addPixelToBuffer (fb, y, x, r, g, b, a);
        }
        else {
            addPixelToBuffer (fb, x, y, r, g, b, a);
        }

        error -= dy;

        if (error < 0) {
            y += ystep;
            error += dx;
        }
    }
}

void drawCircle (FrameBuffer* fb, int x0, int y0, int radius, int r, int g, int b, int a) {
    int x = radius;
    int y = 0;
    int radiusError = 1-x;

    while (x >= y) {
        addPixelToBuffer(fb, x+x0, y+y0, r, g, b, a);
        addPixelToBuffer(fb, y+x0, x+y0, r, g, b, a);
        addPixelToBuffer(fb, -x+x0, y+y0, r, g, b, a);
        addPixelToBuffer(fb, -y+x0, x+y0, r, g, b, a);
        addPixelToBuffer(fb, -x+x0, -y+y0, r, g, b, a);
        addPixelToBuffer(fb, -y+x0, -x+y0, r, g, b, a);
        addPixelToBuffer(fb, x+x0, -y+y0, r, g, b, a);
        addPixelToBuffer(fb, y+x0, -x+y0, r, g, b, a);

        y++;

        if (radiusError < 0) {
            radiusError += 2*y + 1;
        }
        else {
            x--;
            radiusError += 2*(y - x + 1);
        }
    }
}