#include "rasterizer.h"

int findMinX(Vertices vertices[], int vertex_count) {
    int i;
    int yMin = vertices[0]->v.y;
    for (i=0; i<vertex_count; i++) {
        if (vertices[i]->v.y < yMin) {
            yMin = vertices[i]->v.y;
        }
    }
    return yMin;
}

int findMaxY(Vertices vertices[], int vertex_count) {
    int i;
    int yMax = vertices[0]->v.y;
    for (i=0; i<vertex_count; i++) {
        if (vertices[i]->v.y > yMax) {
            yMax = vertices[i]->v.y;
        }
    }
}

void boundaryFill(FrameBuffer* fb, int x, int y, Color c) {
    Color curr = getColor(fb, x, y);
    // printf("(%d, %d): <%d %d %d %d> | <%d %d %d %d>\n", x, y, curr.r, curr.g, curr.b, curr.a, c.r, c.g, c.b, c.a);
    if (!compareColor(curr, c)) {
        addPixelToBuffer(fb, x, y, c.r, c.g, c.b, c.a);
        
        // Recursion
        boundaryFill(fb, x, y-1, c);
        boundaryFill(fb, x, y+1, c);
        boundaryFill(fb, x-1, y, c);
        boundaryFill(fb, x+1, y, c);
    }
}


/**
 * Follow https://www.cosc.brocku.ca/Offerings/3P98/course/lectures/2d/
 * Scan converting solid polygons
 */
void simplePolygonFill(FrameBuffer* fb, Vertex* vertices, int vertex_count, Color c) {
    // Draw outline
    int i;
    for (i = 0; i < vertex_count - 1; ++i) {
        drawLine(fb, vertices[i].x, vertices[i].y,
                vertices[i+1].x, vertices[i+1].y, c);
    }
    drawLine(fb, vertices[0].x, vertices[0].y,
                vertices[vertex_count-1].x, vertices[vertex_count-1].y, c);

    // Get point in polygon
    // TODO: make a better one
    Vertex v = vertices[0];
    v.x++; v.y++;

    // Boundary fill
    boundaryFill(fb, v.x, v.y, c);
    updateFrame(fb);
}