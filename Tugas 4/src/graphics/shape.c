#include "shape.h"

void initPolygon(Polygon *polygon, int vertexCount) {
    polygon->vertices = (Vertex *)malloc(vertexCount * sizeof(Vertex));
    polygon->vertexCount = vertexCount;
}

void initShape(Shape *shape, int polygonCount) {
    shape->polygons = (Polygon *)malloc(polygonCount * sizeof(Polygon));
    shape->polygonCount = polygonCount;
}

void offsetShape(Shape *shape, const Vertex vertex) {
    for (int i = 0; i < shape->polygonCount; ++i) {
        Polygon *polygon = &(shape->polygons[i]);
        for (int j = 0; j < polygon->vertexCount; ++j) {
            polygon->vertices[j].x += vertex.x;
            polygon->vertices[j].y += vertex.y;
        }
    }
}

void normalizeShape(Shape *shape, const Vertex vertex) {
    for (int i = 0; i < shape->polygonCount; ++i) {
        Polygon *polygon = &(shape->polygons[i]);
        for (int j = 0; j < polygon->vertexCount; ++j) {
            polygon->vertices[j].x -= vertex.x;
            polygon->vertices[j].y -= vertex.y;
        }
    }
}

void growShape(Shape *shape, int multiplierScale) {
    for (int i = 0; i < shape->polygonCount; ++i) {
        Polygon *polygon = &(shape->polygons[i]);
        for (int j = 0; j < polygon->vertexCount; ++j) {
            polygon->vertices[j].x *= multiplierScale;
            polygon->vertices[j].y *= multiplierScale;
        }
    }
}

void shrinkShape(Shape *shape, int dividerScale) {
    for (int i = 0; i < shape->polygonCount; ++i) {
        Polygon *polygon = &(shape->polygons[i]);
        for (int j = 0; j < polygon->vertexCount; ++j) {
            polygon->vertices[j].x /= dividerScale;
            polygon->vertices[j].y /= dividerScale;
        }
    }
}

int isCritical(Vertex a, Vertex b, Vertex c) {
    return (a.y < b.y && c.y < b.y) || (a.y > b.y && c.y > b.y);
}

int findMinXInShape(Polygon *polygons, int polygonCount) {
    int xMin = findMinXInPolygon(polygons[0].vertices, polygons[0].vertexCount);
    for (int i = 1; i < polygonCount; i++) {
        int xMinLocal =
            findMinXInPolygon(polygons[i].vertices, polygons[i].vertexCount);
        if (xMinLocal < xMin) {
            xMin = xMinLocal;
        }
    }
    return xMin;
}

int findMaxXInShape(Polygon *polygons, int polygonCount) {
    int xMax = findMaxXInPolygon(polygons[0].vertices, polygons[0].vertexCount);
    for (int i = 1; i < polygonCount; i++) {
        int xMaxLocal =
            findMaxXInPolygon(polygons[i].vertices, polygons[i].vertexCount);
        if (xMaxLocal > xMax) {
            xMax = xMaxLocal;
        }
    }
    return xMax;
}

int findMinYInShape(Polygon *polygons, int polygonCount) {
    int yMin = findMinYInPolygon(polygons[0].vertices, polygons[0].vertexCount);
    for (int i = 1; i < polygonCount; i++) {
        int yMinLocal =
            findMinYInPolygon(polygons[i].vertices, polygons[i].vertexCount);
        if (yMinLocal < yMin) {
            yMin = yMinLocal;
        }
    }
    return yMin;
}

int findMaxYInShape(Polygon *polygons, int polygonCount) {
    int yMax = findMaxYInPolygon(polygons[0].vertices, polygons[0].vertexCount);
    for (int i = 1; i < polygonCount; i++) {
        int yMaxLocal =
            findMaxYInPolygon(polygons[i].vertices, polygons[i].vertexCount);
        if (yMaxLocal > yMax) {
            yMax = yMaxLocal;
        }
    }
    return yMax;
}

int findMinXInPolygon(Vertex *vertices, int vertexCount) {
    int xMin = vertices[0].x;
    for (int i = 0; i < vertexCount; i++) {
        if (vertices[i].x < xMin) {
            xMin = vertices[i].x;
        }
    }
    return xMin;
}

int findMaxXInPolygon(Vertex *vertices, int vertexCount) {
    int xMax = vertices[0].x;
    for (int i = 1; i < vertexCount; i++) {
        if (vertices[i].x > xMax) {
            xMax = vertices[i].x;
        }
    }
    return xMax;
}

int findMinYInPolygon(Vertex *vertices, int vertexCount) {
    int yMin = vertices[0].y;
    for (int i = 1; i < vertexCount; i++) {
        if (vertices[i].y < yMin) {
            yMin = vertices[i].y;
        }
    }
    return yMin;
}

int findMaxYInPolygon(Vertex *vertices, int vertexCount) {
    int yMax = vertices[0].y;
    for (int i = 1; i < vertexCount; i++) {
        if (vertices[i].y > yMax) {
            yMax = vertices[i].y;
        }
    }
    return yMax;
}
