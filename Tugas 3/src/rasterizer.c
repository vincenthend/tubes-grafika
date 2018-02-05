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

void scanlineFill(FrameBuffer *fb, Shape *s, Color c) {
    int i;
    Color white;
    initColor(&white, "FFFFFF");

    for (i = 0; i < s->count; ++i) {
        drawPolygon(fb, &(s->polygons[i]), white);
    }

    int minX = findMinXInShape(s->polygons, s->count);
    int maxX = findMaxXInShape(s->polygons, s->count);
    int minY = findMinYInShape(s->polygons, s->count);
    int maxY = findMaxYInShape(s->polygons, s->count);

    int y;
    int colorize = 0;
    for (y = minY; y <= maxY; y++) {
        Color curr = getColor(fb, minX, y);
        colorize = 0;

        int x;
        for (x = minX; x <= maxX; x++) {
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
}

void fillShape(FrameBuffer *fb, Shape *s, Color c) {
    int i;
    printf("Preparing to draw polygon\n");
    for (i = 0; i < s->count; ++i) {
        drawPolygon(fb, &(s->polygons[i]), c);
    }

    // Get point in polygon
    // TODO: make a better one
    printf("Finished drawing polygon\n");
    Vertex v = (*s).polygons[0].vertices[0];
    v.x++;
    v.y++;

    // Boundary fill
    printf("Boundary Fill\n");
    boundaryFill(fb, v.x, v.y, c);

    // Scanline fill
    // scanlineFill(fb, s, c);

    updateFrame(fb);
}

void fillChar(FrameBuffer *fb, char ch, RasterFont *rf, Vertex offset,
              Color c) {
    printf("count: %d\n", (*rf).dict[(int)ch].count);
    offsetShape(&(rf->dict[(int)ch]), offset);
    fillShape(fb, &(rf->dict[(int)ch]), c);
}

void fillString(FrameBuffer *fb, char *s, RasterFont *rf, Vertex offset,
                Color c) {
    Vertex origin = offset;
    int len = strlen(s);

    int i;
    for (i = 0; i < len; ++i) {
        //Ini yang gw ubah --AGUS s[i]
        fillChar(fb, s[i], rf, offset, c);

        // Manage offset
        if (offset.x + 2 * rf->width >= fb->screen_width) {
            offset.x = origin.x;
            offset.y += rf->height;

            if (offset.y >= fb->screen_height)
                return;
        } else {
            offset.x += rf->width;
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
