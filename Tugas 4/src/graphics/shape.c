#include <math.h>
#include "shape.h"

void initPolygon(Polygon *polygon, int vertexCount) {
    polygon->vertices = (Vertex *)malloc(vertexCount * sizeof(Vertex));
    polygon->vertexCount = vertexCount;
}

void initShape(Shape *shape, int polygonCount) {
    shape->polygons = (Polygon *)malloc(polygonCount * sizeof(Polygon));
    shape->polygonCount = polygonCount;
}

void cloneShape(const Shape* src, Shape* dest) {
    initShape(dest, src->polygonCount);
    printf("Polygon: %d\n", dest->polygonCount);
    for (int i = 0; i < src->polygonCount; ++i) {
        printf("Init polygon %d\n", i);
        Polygon *srcPolygon = &(src->polygons[i]);
        initPolygon(&(dest->polygons[i]), srcPolygon->vertexCount);
        Polygon *destPolygon = &(dest->polygons[i]);

        printf("Clone polygon %d\n", i);
        for (int j = 0; j < srcPolygon->vertexCount; ++j) {
            destPolygon->vertices[j].x = srcPolygon->vertices[j].x;
            destPolygon->vertices[j].y = srcPolygon->vertices[j].y;
        }
        printf("Polygon %d copied\n", i);
    }
    printf("Shape copied\n");
}

void destroyShape(Shape *shape) {
    for (int i = 0; i < shape->polygonCount; ++i) {
        free(shape->polygons[i].vertices);
    }
    free(shape->polygons);
}

void offsetShape(Shape *shape, const Vertex vertex) {
    for (int i = 0; i < shape->polygonCount; ++i) {
        Polygon *polygon = &(shape->polygons[i]);
        for (int j = 0; j < polygon->vertexCount; ++j) {
            printf("(%d, %d)->", polygon->vertices[j].x, polygon->vertices[j].y);

            polygon->vertices[j].x += vertex.x;
            polygon->vertices[j].y += vertex.y;

            printf("(%d, %d)\n", polygon->vertices[j].x, polygon->vertices[j].y);
        }
    }
}

void normalizeShapeOffset(Shape *shape, const Vertex vertex) {
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

void normalizeShapeAfterRotation(Shape *shape) {
    int xMin = shape->polygons[0].vertices[0].x;
    int yMin = shape->polygons[0].vertices[0].y;
    int xMax = xMin;
    int yMax = yMin;

    for (int i = 0; i < shape->polygonCount; ++i) {
        Polygon *p = &(shape->polygons[i]);
        for (int j = 0; j < p->vertexCount; ++j) {
            Vertex *v =  &(p->vertices[j]);

            if (v->x < xMin)
                xMin = v->x;
            else if (v->x > xMax)
                xMax = v->x;
            if (v->y < yMin)
                yMin = v->y;
            else if (v->y > yMax)
                yMax = v->y;
        }
    }

    Vertex offset = (Vertex) { -xMin, -yMin };
    offsetShape(shape, offset);
}

void rotateShape(Shape *shape, const int degrees) {
    const float radians = degrees * M_PI / 180;
    const float sin = sinf(radians);
    const float cos = cosf(radians);

    for (int i = 0; i < shape->polygonCount; ++i) {
        Polygon *p = &(shape->polygons[i]);
        for (int j = 0; j < p->vertexCount; ++j) {
            Vertex *v = &(p->vertices[j]);

            float x2 = cos * v->x - sin * v->y;
            float y2 = sin * v->x + cos * v->y;

            v->x = round(x2);
            v->y = round(y2);
        }
    }
    normalizeShapeAfterRotation(shape);
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
