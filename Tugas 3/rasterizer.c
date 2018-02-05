#include <string.h>

#include "rasterizer.h"

void initPolygon(Polygon *p, int n) {
    p->vertices = (Vertex *)malloc(n * sizeof(Vertex));
    p->count = n;
}

void initShape(Shape *s, int n) {
    s->polygons = (Polygon *)malloc(n * sizeof(Polygon));
    s->count = n;
}

void initRasterFont(RasterFont *rasterFont) {
    rasterFont->dict = (Shape *)malloc(256 * sizeof(Shape));
    rasterFont->height = 90;
    rasterFont->width = 110;
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

void offsetShape(Shape *s, const Vertex v) {
    int i, j;
    printf("Offset shape\n");
    printf("%d\n", (*s).count);
    for (i = 0; i < (*s).count; ++i) {
        Polygon *p = &(s->polygons[i]);
        for (j = 0; j < p->count; ++j) {
            p->vertices[j].x += v.x;
            p->vertices[j].y += v.y;
        }
    }
    printf("Finished offset\n");
}

/* ---- min-max related ---- */

int findMinXInShape(Polygon *polygons, int polygon_count) {
    int i;
    int xMin = findMinXInPolygon(polygons[0].vertices, polygons[0].count);
    for (i = 1; i < polygon_count; i++) {
        int xMinLocal =
            findMinXInPolygon(polygons[i].vertices, polygons[i].count);
        if (xMinLocal < xMin) {
            xMin = xMinLocal;
        }
    }
    return xMin;
}

int findMaxXInShape(Polygon *polygons, int polygon_count) {
    int i;
    int xMax = findMaxXInPolygon(polygons[0].vertices, polygons[0].count);
    for (i = 1; i < polygon_count; i++) {
        int xMaxLocal =
            findMaxXInPolygon(polygons[i].vertices, polygons[i].count);
        if (xMaxLocal > xMax) {
            xMax = xMaxLocal;
        }
    }
    return xMax;
}

int findMinYInShape(Polygon *polygons, int polygon_count) {
    int i;
    int yMin = findMinYInPolygon(polygons[0].vertices, polygons[0].count);
    for (i = 1; i < polygon_count; i++) {
        int yMinLocal =
            findMinYInPolygon(polygons[i].vertices, polygons[i].count);
        if (yMinLocal < yMin) {
            yMin = yMinLocal;
        }
    }
    return yMin;
}

int findMaxYInShape(Polygon *polygons, int polygon_count) {
    int i;
    int yMax = findMaxYInPolygon(polygons[0].vertices, polygons[0].count);
    for (i = 1; i < polygon_count; i++) {
        int yMaxLocal =
            findMaxYInPolygon(polygons[i].vertices, polygons[i].count);
        if (yMaxLocal > yMax) {
            yMax = yMaxLocal;
        }
    }
    return yMax;
}

int findMinXInPolygon(Vertex *vertices, int vertex_count) {
    int i;
    int xMin = vertices[0].x;
    for (i = 0; i < vertex_count; i++) {
        if (vertices[i].x < xMin) {
            xMin = vertices[i].x;
        }
    }
    return xMin;
}

int findMaxXInPolygon(Vertex *vertices, int vertex_count) {
    int i;
    int xMax = vertices[0].x;
    for (i = 1; i < vertex_count; i++) {
        if (vertices[i].x > xMax) {
            xMax = vertices[i].x;
        }
    }
    return xMax;
}

int findMinYInPolygon(Vertex *vertices, int vertex_count) {
    int i;
    int yMin = vertices[0].y;
    for (i = 1; i < vertex_count; i++) {
        if (vertices[i].y < yMin) {
            yMin = vertices[i].y;
        }
    }
    return yMin;
}

int findMaxYInPolygon(Vertex *vertices, int vertex_count) {
    int i;
    int yMax = vertices[0].y;
    for (i = 1; i < vertex_count; i++) {
        if (vertices[i].y > yMax) {
            yMax = vertices[i].y;
        }
    }
    return yMax;
}
