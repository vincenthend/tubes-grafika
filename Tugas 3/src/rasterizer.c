#include <string.h>

#include "rasterizer.h"

void boundaryFillHelper(FrameBuffer *fb, int x, int y, Color color) {
    // Check screen boundaries
    if ((x < 0) || (x >= fb->screen_width) || (y < 0) ||
        (y >= fb->screen_height))
        return;

    // Output to screen
    Color curr = getColor(fb, x, y);
    if (!isSameColor(curr, color)) {
        addPixelToBuffer(fb, x, y, color.r, color.g, color.b, color.a);
        boundaryFillHelper(fb, x, y - 1, color);
        boundaryFillHelper(fb, x, y + 1, color);
        boundaryFillHelper(fb, x - 1, y, color);
        boundaryFillHelper(fb, x + 1, y, color);
    }
}

void boundaryFill(FrameBuffer *fb, Shape *s, Color color) {
    int x = findMinXInShape(s->polygons, s->polygonCount);
    int y = findMinYInShape(s->polygons, s->polygonCount) + 3;

    Color curr = getColor(fb, x, y);

    while (!isSameColor(curr, color)) {
        x++;
        curr = getColor(fb, x, y);
    }

    Vertex vertex;
    vertex.x = x + 2;
    vertex.y = y + 2;

    boundaryFillHelper(fb, vertex.x, vertex.y, color);
}

int inCriticalList(int x, int y, Vertex *vertices, int vertexCount) {
    int retVal = 0;
    int i = 0;
    while (i < vertexCount && retVal == 0) {
        if ((vertices[i].x == x && vertices[i].y == y) ||
            (vertices[i].x == x && vertices[i].y + 1 == y)) {
            retVal = 1;
        } else {
            i++;
        }
    }

    return retVal;
}

void scanlineFill(FrameBuffer *fb, Shape *s, Color c) {

    Vertex vertices[999];
    int vertexCount = 0;

    int minX = findMinXInShape(s->polygons, s->polygonCount);
    int maxX = findMaxXInShape(s->polygons, s->polygonCount);
    int minY = findMinYInShape(s->polygons, s->polygonCount);
    int maxY = findMaxYInShape(s->polygons, s->polygonCount);

    for (int i = 0; i < s->polygonCount; ++i) {
        drawPolygon(fb, &(s->polygons[i]), c);

        //Find critical vertex
        if (isCritical(
                (*s).polygons[i].vertices[(*s).polygons[i].vertexCount - 1],
                (*s).polygons[i].vertices[0],
                (*s).polygons[i].vertices[1]) == 1) {
            vertices[vertexCount] = (*s).polygons[i].vertices[0];
            vertexCount++;
        }

        int j;
        for (j = 1; j < (*s).polygons[i].vertexCount - 1; j++) {
            if (isCritical((*s).polygons[i].vertices[j - 1],
                           (*s).polygons[i].vertices[j],
                           (*s).polygons[i].vertices[j + 1]) == 1) {
                vertices[vertexCount] = (*s).polygons[i].vertices[j];
                vertexCount++;
            }
        }

        if (isCritical((*s).polygons[i].vertices[j - 1],
                       (*s).polygons[i].vertices[j],
                       (*s).polygons[i].vertices[0]) == 1) {
            vertices[vertexCount] = (*s).polygons[i].vertices[j];
            vertexCount++;
        }
    }

    // Color Fill
    int colorize = 0;
    int threshold = 10;
    int adj_pixel_counter = 0;
    for (int y = minY; y <= maxY; y++) {
        Color curr = getColor(fb, minX, y);
        colorize = 0;
        adj_pixel_counter = 0;
        for (int x = minX; x <= maxX; x++) {
            curr = getColor(fb, x, y);
            if (isSameColor(curr, c)) {
                adj_pixel_counter++;
                if (inCriticalList(x, y, vertices, vertexCount) == 0) {
                    colorize = !colorize;
                } else {
                    printf("in %d, %d\n", x, y);
                }
            } else if (colorize) {
                if (adj_pixel_counter > threshold) {
                    colorize = !colorize;
                } else {
                    addPixelToBuffer(fb, x, y, c.r, c.g, c.b, c.a);
                }
            }
        }
    }
}

void fillShape(FrameBuffer *fb, Shape *s, Color color) {
    for (int i = 0; i < s->polygonCount; ++i) {
        drawPolygon(fb, &(s->polygons[i]), color);
    }

    // Boundary fill
    boundaryFill(fb, s, color);

    // Scanline fill
    // scanlineFill(fb, s, color);
}

void fillChar(FrameBuffer *fb, char c, RasterFont *rf, Vertex offset,
              Color color) {
    offsetShape(&(rf->dict[(int)c]), offset);
    fillShape(fb, &(rf->dict[(int)c]), color);
    normalizeShape(&(rf->dict[(int)c]), offset);
}

void fillString(FrameBuffer *fb, char *s, RasterFont *rf, Vertex offset,
                Color color) {
    Vertex origin = offset;
    int len = strlen(s);

    int i;
    for (i = 0; i < len; ++i) {
        if (s[i] == ' ') {

        } else {
            fillChar(fb, s[i], rf, offset, color);
        }

        // Manage offset
        if (offset.x + 2 * rf->width >= fb->screen_width) {
            offset.x = origin.x;
            offset.y += rf->height + 10;

            if (offset.y >= fb->screen_height)
                return;
        } else {
            offset.x += rf->width;
        }
    }
}

void fillSquareArea(FrameBuffer *fb, int x0, int y0, int x1, int y1,
                    Color color) {
    for (int x = x0; x <= x1; x++) {
        for (int y = y0; y <= y1; y++) {
            addPixelToBuffer(fb, x, y, color.r, color.g, color.b, color.a);
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
