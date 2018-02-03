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

/**
 * Follow https://www.cosc.brocku.ca/Offerings/3P98/course/lectures/2d/
 * Scan converting solid polygons
 */
void simplePolygonFill(Vertex* vertices, int vertex_count, Color c) {

}