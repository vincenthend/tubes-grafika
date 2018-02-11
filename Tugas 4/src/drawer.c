#include "drawer.h"

void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void drawLine(FrameBuffer *fb, int x0, int y0, int x1, int y1, Color color) {
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
        if (x >= 0 && x <= fb->screen_width && y >= 0 && y <= fb->screen_width) {
            if (steep) {
                addPixelToBuffer(fb, y, x, color.r, color.g, color.b, color.a);
            } else {
                addPixelToBuffer(fb, x, y, color.r, color.g, color.b, color.a);
            }
        }

        error -= dy;

        if (error < 0) {
            y += ystep;
            error += dx;
        }
    }
}

void drawThickLine(FrameBuffer *fb, int x0, int y0, int x1, int y1, int width,
                   Color color) {
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
            drawFilledCircle(fb, y, x, width, color);
        } else {
            drawFilledCircle(fb, x, y, width, color);
        }

        error -= dy;

        if (error < 0) {
            y += ystep;
            error += dx;
        }
    }
}

void drawCircle(FrameBuffer *fb, int x0, int y0, int radius, Color color) {
    int x = radius;
    int y = 0;
    int radiusError = 1 - x;

    while (x >= y) {
        addPixelToBuffer(fb, x + x0, y + y0, color.r, color.g, color.b,
                         color.a);
        addPixelToBuffer(fb, y + x0, x + y0, color.r, color.g, color.b,
                         color.a);
        addPixelToBuffer(fb, -x + x0, y + y0, color.r, color.g, color.b,
                         color.a);
        addPixelToBuffer(fb, -y + x0, x + y0, color.r, color.g, color.b,
                         color.a);
        addPixelToBuffer(fb, -x + x0, -y + y0, color.r, color.g, color.b,
                         color.a);
        addPixelToBuffer(fb, -y + x0, -x + y0, color.r, color.g, color.b,
                         color.a);
        addPixelToBuffer(fb, x + x0, -y + y0, color.r, color.g, color.b,
                         color.a);
        addPixelToBuffer(fb, y + x0, -x + y0, color.r, color.g, color.b,
                         color.a);

        y++;

        if (radiusError < 0) {
            radiusError += 2 * y + 1;
        } else {
            x--;
            radiusError += 2 * (y - x + 1);
        }
    }
}

void drawFilledCircle(FrameBuffer *fb, int x0, int y0, int radius,
                      Color color) {
    for (int currentRadius = 1; currentRadius <= radius; currentRadius++) {
        int x = radius;
        int y = 0;
        int radiusError = 1 - x;

        while (x >= y) {
            addPixelToBuffer(fb, x + x0, y + y0, color.r, color.g, color.b,
                             color.a);
            addPixelToBuffer(fb, y + x0, x + y0, color.r, color.g, color.b,
                             color.a);
            addPixelToBuffer(fb, -x + x0, y + y0, color.r, color.g, color.b,
                             color.a);
            addPixelToBuffer(fb, -y + x0, x + y0, color.r, color.g, color.b,
                             color.a);
            addPixelToBuffer(fb, -x + x0, -y + y0, color.r, color.g, color.b,
                             color.a);
            addPixelToBuffer(fb, -y + x0, -x + y0, color.r, color.g, color.b,
                             color.a);
            addPixelToBuffer(fb, x + x0, -y + y0, color.r, color.g, color.b,
                             color.a);
            addPixelToBuffer(fb, y + x0, -x + y0, color.r, color.g, color.b,
                             color.a);

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

void drawSquare(FrameBuffer *fb, int x0, int y0, int x1, int y1, Color color) {
    drawLine(fb, x0, y0, x0, y1, color);
    drawLine(fb, x0, y1, x1, y1, color);
    drawLine(fb, x1, y1, x1, y0, color);
    drawLine(fb, x1, y0, x0, y0, color);
}

void drawMonoImage(FrameBuffer *fb, Image image, int x, int y, Color color) {
    char *data = image.data;
    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) {
            if (data[i * image.width + j] == '1') {
                addPixelToBuffer(fb, (x) + j, (y) + i, color.r, color.g,
                                 color.b, color.a);
            }
        }
    }
}

void drawPolygon(FrameBuffer *fb, const Polygon *polygon, Color color) {
    for (int i = 0; i < polygon->vertexCount - 1; ++i) {
        drawLine(fb, polygon->vertices[i].x, polygon->vertices[i].y,
                 polygon->vertices[i + 1].x, polygon->vertices[i + 1].y, color);
    }
    drawLine(fb, polygon->vertices[0].x, polygon->vertices[0].y,
             polygon->vertices[polygon->vertexCount - 1].x,
             polygon->vertices[polygon->vertexCount - 1].y, color);
}
