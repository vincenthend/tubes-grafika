#include "vertex.h"

void scaleVertex(Vertex *v, float scale, Vertex pivot) {
    Vertex temp = (Vertex){round((v->x - pivot.x) * scale + pivot.x),
                           round((v->y - pivot.y) * scale + pivot.y)};
    *v = (Vertex){temp.x, temp.y};
}

int isVertexCritical(Vertex a, Vertex b, Vertex c) {
    return (a.y < b.y && c.y < b.y) || (a.y > b.y && c.y > b.y);
}

float vertexDistance(Vertex a, Vertex b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}
