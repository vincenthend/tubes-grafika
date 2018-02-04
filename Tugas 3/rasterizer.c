#include "rasterizer.h"
#include "rasterizer_extended.c"

void initPolygon(Polygon *p, int n) {
    p->vertices = (Vertex *)malloc(n * sizeof(Vertex));
    p->count = n;
}

void initShape(Shape *s, int n) {
    s->polygons = (Polygon *)malloc(n * sizeof(Polygon));
    s->count = n;
}

void drawPolygon(FrameBuffer *fb, const Polygon *p, Color c) {
    int i;
    for (i = 0; i < p->count - 1; ++i) {
        drawLine(fb, p->vertices[i].x, p->vertices[i].y, p->vertices[i + 1].x,
                 p->vertices[i + 1].y, c);
    }
    drawLine(fb, p->vertices[0].x, p->vertices[0].y,
             p->vertices[p->count - 1].x, p->vertices[p->count - 1].y, c);
}

void boundaryFill(FrameBuffer *fb, int x, int y, Color c) {
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
    int minX = findMinXInShape(s->polygons, s->count);
    int maxX = findMaxXInShape(s->polygons, s->count);
    int minY = findMinYInShape(s->polygons, s->count);
    int maxY = findMaxYInShape(s->polygons, s->count);

    int y;
    int colorize = 1;
    for (y = minY; y <= maxY; y++) {
        Color curr = getColor(fb, minX, y);
        if (!isSameColor(curr, c)) {
            colorize = 0;
        }

        int x;
        for (x = minX; x <= maxX; x++) {
            curr = getColor(fb, x, y);
            if (isSameColor(curr, c)) {
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
    for (i = 0; i < s->count; ++i) {
        drawPolygon(fb, &(s->polygons[i]), c);
    }

    // Get point in polygon
    // TODO: make a better one
    Vertex v = s->polygons[0].vertices[0];
    v.x++;
    v.y++;

    // Boundary fill
    boundaryFill(fb, v.x, v.y, c);

    // Scanline fill
    // scanlineFill(fb, s, c);

    updateFrame(fb);
}

void initializeFontShape() {
    raster_cdict['a']
}

void fillChar(FrameBuffer *fb, char ch, int x, int y, Color c) {

}

void fillString(FrameBuffer *fb, char *s, int x, int y, Color c) {

}
