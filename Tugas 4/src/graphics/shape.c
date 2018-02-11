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

int* findMinMaxShape(Shape *shape) {
    static int minMaxXY[4];
    /**
     * Index 0: minX
     * Index 1: maxX
     * Index 2: minY
     * Index 3: maxY
     */
    minMaxXY[0] = 9999;
    minMaxXY[1] = -1;
    minMaxXY[2] = 9999;
    minMaxXY[3] = -1;

    for (int i = 0; i < shape->polygonCount; ++i) {
        Polygon *polygon = &(shape->polygons[i]);
        for (int j = 0; j < polygon->vertexCount; ++j) {
            if (polygon->vertices[j].x < minMaxXY[0]) {
                minMaxXY[0] = polygon->vertices[j].x;
            }
            if (polygon->vertices[j].x > minMaxXY[1]) {
                minMaxXY[1] = polygon->vertices[j].x;
            }
            if (polygon->vertices[j].y < minMaxXY[2]) {
                minMaxXY[2] = polygon->vertices[j].y;
            }
            if (polygon->vertices[j].y > minMaxXY[3]) {
                minMaxXY[3] = polygon->vertices[j].y;
            }
        }
    }

    return minMaxXY;
}

void cloneShape(const Shape* src, Shape* dest) {
    initShape(dest, src->polygonCount);
    for (int i = 0; i < src->polygonCount; ++i) {
        Polygon *srcPolygon = &(src->polygons[i]);
        initPolygon(&(dest->polygons[i]), srcPolygon->vertexCount);
        Polygon *destPolygon = &(dest->polygons[i]);

        for (int j = 0; j < srcPolygon->vertexCount; ++j) {
            destPolygon->vertices[j].x = srcPolygon->vertices[j].x;
            destPolygon->vertices[j].y = srcPolygon->vertices[j].y;
        }
    }
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
            polygon->vertices[j].x += vertex.x;
            polygon->vertices[j].y += vertex.y;
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

void calculateBoundaries(Shape *shape) {
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

    shape->upperLeft = (Vertex) { xMin, yMin };
    shape->lowerRight = (Vertex) { xMax, yMax };
    shape->center = (Vertex) {
        round((xMin + xMax) / 2),
        round((yMin + yMax) / 2)
    };
}

void prepareShapeForRotation(Shape *shape) {
    calculateBoundaries(shape);

    int radius = round(distance(shape->upperLeft, shape->center));
    Vertex offset = (Vertex) {
        radius - shape->center.x + shape->upperLeft.x,
        radius - shape->center.y + shape->upperLeft.y
    };

    offsetShape(shape, offset);
    calculateBoundaries(shape);
}

void rotateShape(Shape *shape, const int degrees) {
    const float radians = degrees * M_PI / 180;
    const float sin = sinf(radians);
    const float cos = cosf(radians);
    const Vertex *offset = &(shape->center);

    for (int i = 0; i < shape->polygonCount; ++i) {
        Polygon *p = &(shape->polygons[i]);
        for (int j = 0; j < p->vertexCount; ++j) {
            Vertex *v = &(p->vertices[j]);

            float x2 = cos * (v->x - offset->x) - sin * (v->y - offset->y);
            float y2 = sin * (v->x - offset->x) + cos * (v->y - offset->y);

            v->x = round(x2 + offset->x);
            v->y = round(y2 + offset->y);
        }
    }
    calculateBoundaries(shape);
}

void rotateShapewithPivot(Shape *shape, const int degrees, Vertex pivot) {
    const float radians = degrees * M_PI / 180;
    const float sin = sinf(radians);
    const float cos = cosf(radians);
    const Vertex *offset = &(pivot);

    for (int i = 0; i < shape->polygonCount; ++i) {
        Polygon *p = &(shape->polygons[i]);
        for (int j = 0; j < p->vertexCount; ++j) {
            Vertex *v = &(p->vertices[j]);

            float x2 = cos * (v->x - offset->x) - sin * (v->y - offset->y);
            float y2 = sin * (v->x - offset->x) + cos * (v->y - offset->y);

            v->x = round(x2 + offset->x);
            v->y = round(y2 + offset->y);
        }
    }
    calculateBoundaries(shape);
}

int isCritical(Vertex a, Vertex b, Vertex c) {
    return (a.y < b.y && c.y < b.y) || (a.y > b.y && c.y > b.y);
}

float distance(Vertex a, Vertex b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}