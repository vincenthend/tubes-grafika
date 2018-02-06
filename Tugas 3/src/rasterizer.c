#include <string.h>

#include "rasterizer.h"

void boundaryFill(FrameBuffer *fb, int x, int y, Color c) {
    // Check screen boundaries
    if ((x < 0) || (x >= fb->screen_width) || (y < 0) ||
        (y >= fb->screen_height))
        return;

    // Output to screen
    Color curr = getColor(fb, x, y);
    if (!isSameColor(curr, c)) {
        addPixelToBuffer(fb, x, y, c.r, c.g, c.b, c.a);
        boundaryFill(fb, x, y - 1, c);
        boundaryFill(fb, x, y + 1, c);
        boundaryFill(fb, x - 1, y, c);
        boundaryFill(fb, x + 1, y, c);
    }
}

void scanlineFill(FrameBuffer *fb, Shape *s, Color c, int arr[]) {
    Color white;
    initColor(&white, "FFFFFF");

    int minX = findMinXInShape(s->polygons, s->polygonCount);
    int maxX = findMaxXInShape(s->polygons, s->polygonCount);
    int minY = findMinYInShape(s->polygons, s->polygonCount);
    int maxY = findMaxYInShape(s->polygons, s->polygonCount);

    for (int i = 0; i < s->polygonCount; ++i) {
        drawPolygon(fb, &(s->polygons[i]), white);
    }

    int colorize = 0;

    int passCounter = 0;
    // int dummyCounter = 0;
    for (int y = minY + 1; y < maxY; y++) {
        if (y == minY + arr[passCounter]) {
            // printf("%d\n", y);
            passCounter++; //do nothing
        } else { //
            Color curr = getColor(fb, minX, y);
            colorize = 0;

            for (int x = minX; x <= maxX; x++) {
                curr = getColor(fb, x, y);
                if (isSameColor(curr, white)) {
                    colorize = !colorize;

                    continue;
                }

                if (colorize) {
                    addPixelToBuffer(fb, x, y, c.r, c.g, c.b, c.a);
                }
            }
        }
        // printf("%d\n", dummyCounter);
        // usleep(200000);
        // dummyCounter++;
    }

}

void fillShape(FrameBuffer *fb, Shape *s, Color color, char c) {
    for (int i = 0; i < s->polygonCount; ++i) {
        drawPolygon(fb, &(s->polygons[i]), color);
    }

    // Get point in polygon
    // TODO: make a better one
    Vertex v = s->polygons[0].vertices[0];
    v.x++;
    v.y++;

    // Boundary fill
    // boundaryFill(fb, v.x, v.y, c);

    // Scanline fill
    if (c == 'a') {
        int arr[5] = {1, 34, 35, 75, 90};
        scanlineFill(fb, s, color, arr); 
    } else if (c == 'b') {
        int arr[2] = {100, 107};
        scanlineFill(fb, s, color, arr);
    } else if (c == 'c') {
        int arr[1] = {0};
        scanlineFill(fb, s, color, arr);
    } else if (c == 'd') {
        int arr[1] = {0};
        scanlineFill(fb, s, color, arr);
    } else if (c == 'e') {
        int arr[1] = {0};
        scanlineFill(fb, s, color, arr);
    } else if (c == 'f') {
        int arr[1] = {0};
        scanlineFill(fb, s, color, arr);
    } else if (c == 'g') {
        int arr[2] = {14, 96};
        scanlineFill(fb, s, color, arr);
    } else if (c == 'h') {
        int arr[1] = {0};
        scanlineFill(fb, s, color, arr);
    } else if (c == 'i') {
        int arr[1] = {0};
        scanlineFill(fb, s, color, arr);
    } else if (c == 'j') {
        int arr[2] = {79, 103};
        scanlineFill(fb, s, color, arr);
    } else if (c == 'k') {
        int arr[7] = {6, 17, 22, 28, 39, 44, 53};
        scanlineFill(fb, s, color, arr);
    } else if (c == 'l') {
        int arr[1] = {0};
        scanlineFill(fb, s, color, arr);
    } else if (c == 'm') {
        int arr[3] = {31, 47, 75};
        scanlineFill(fb, s, color, arr);
    } else if (c == 'n') {
        int arr[1] = {33};
        scanlineFill(fb, s, color, arr);
    } else if (c == 'o') {
        int arr[2] = {16, 94};
        scanlineFill(fb, s, color, arr);
    } else if (c == 'p') {
        int arr[5] = {2, 7, 56, 59, 60};
        scanlineFill(fb, s, color, arr);
    } else if (c == 'q') {
        int arr[3] = {73, 105, 107};
        scanlineFill(fb, s, color, arr);
    } else if (c == 'r') {
        int arr[6] = {7, 49, 51, 53, 55, 56};
        scanlineFill(fb, s, color, arr);
    } else if (c == 's') {
        int arr[4] = {15, 52, 58, 85};
        scanlineFill(fb, s, color, arr);
    } else if (c == 't') {
        int arr[1] = {0};
        scanlineFill(fb, s, color, arr);
    } else if (c == 'u') {
        int arr[1] = {0};
        scanlineFill(fb, s, color, arr);
    } else if (c == 'v') {
        int arr[3] = {71, 72, 109};
        scanlineFill(fb, s, color, arr);
    } else if (c == 'w') {
        int arr[4] = {75, 78, 79, 80};
        scanlineFill(fb, s, color, arr);
    } else if (c == 'x') {
        int arr[2] = {40, 70};
        scanlineFill(fb, s, color, arr);
    } else if (c == 'y') {
        int arr[1] = {40};
        scanlineFill(fb, s, color, arr);
    } else if (c == 'z') {
        int arr[1] = {0};
        scanlineFill(fb, s, color, arr);
    }

    updateFrame(fb);
}

void fillChar(FrameBuffer *fb, char ch, RasterFont *rasterFont, Vertex offset,
              Color c) {
    offsetShape(&(rasterFont->dict[(int)ch]), offset);
    fillShape(fb, &(rasterFont->dict[(int)ch]), c, ch);
}

void fillString(FrameBuffer *fb, char *s, RasterFont *rasterFont, Vertex offset,
                Color c) {
    Vertex origin = offset;
    int len = strlen(s);

    int i;
    for (i = 0; i < len; ++i) {
        fillChar(fb, s[i], rasterFont, offset, c);

        // Manage offset
        if (offset.x + 2 * rasterFont->width >= fb->screen_width) {
            offset.x = origin.x;
            offset.y += rasterFont->height;

            if (offset.y >= fb->screen_height)
                return;
        } else {
            offset.x += rasterFont->width;
        }
    }
}

void fillSquareArea(FrameBuffer *fb, int x0, int y0, int x1, int y1, Color c) {
    for (int x = x0; x <= x1; x++) {
        for (int y = y0; y <= y1; y++) {
            addPixelToBuffer(fb, x, y, c.r, c.g, c.b, c.a);
        }
    }
}

void fillRainbow(FrameBuffer *fb, int x, int y) {
    Color red, orange, yellow, green, blue, purple;
    initColor(&red, "FF0000");
    initColor(&orange, "FF7700");
    initColor(&yellow, "FFFF00");
    initColor(&green, "009900");
    initColor(&blue, "000099");
    initColor(&purple, "990099");

    fillSquareArea(fb, x - 8, y + 4, x + 20, y + 6, red);
    fillSquareArea(fb, x - 8, y + 7, x + 20, y + 9, orange);
    fillSquareArea(fb, x - 8, y + 10, x + 20, y + 12, yellow);
    fillSquareArea(fb, x - 8, y + 13, x + 20, y + 15, green);
    fillSquareArea(fb, x - 8, y + 16, x + 20, y + 18, blue);
    fillSquareArea(fb, x - 8, y + 19, x + 20, y + 21, purple);
}
