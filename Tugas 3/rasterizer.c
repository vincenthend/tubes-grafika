#include "rasterizer.h"

void initPolygon(Polygon *p, int n) {
    p->vertices = (Vertex *)malloc(n * sizeof(Vertex));
    p->count = n;
}

void initShape(Shape *s, int n) {
    s->polygons = (Polygon *)malloc(n * sizeof(Polygon));
    s->count = n;
}

// int findMinX(Vertices vertices[], int vertex_count) {
//     int i;
//     int yMin = vertices[0]->v.y;
//     for (i = 0; i < vertex_count; i++) {
//         if (vertices[i]->v.y < yMin) {
//             yMin = vertices[i]->v.y;
//         }
//     }
//     return yMin;
// }

// int findMaxY(Vertices vertices[], int vertex_count) {
//     int i;
//     int yMax = vertices[0]->v.y;
//     for (i = 0; i < vertex_count; i++) {
//         if (vertices[i]->v.y > yMax) {
//             yMax = vertices[i]->v.y;
//         }
//     }
// }

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

/**
 * Follow https://www.cosc.brocku.ca/Offerings/3P98/course/lectures/2d/
 * Scan converting solid polygons
 */
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
    updateFrame(fb);
}
