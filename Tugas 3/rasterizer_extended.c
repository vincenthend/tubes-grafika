#include "rasterizer.h"

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
