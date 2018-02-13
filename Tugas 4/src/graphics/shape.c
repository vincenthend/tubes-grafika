#include "shape.h"

#define max(a, b)                                                              \
    ({                                                                         \
        __typeof__(a) _a = (a);                                                \
        __typeof__(b) _b = (b);                                                \
        _a > _b ? _a : _b;                                                     \
    })

#define M_PI 3.14159265358979323846

void initPolygon(Polygon *polygon, int vertexCount) {
    polygon->vertices = (Vertex *)malloc(vertexCount * sizeof(Vertex));
    polygon->vertexCount = vertexCount;
}

void initShape(Shape *shape, int polygonCount) {
    shape->polygons = (Polygon *)malloc(polygonCount * sizeof(Polygon));
    shape->polygonCount = polygonCount;
}

void cloneShape(const Shape *src, Shape *dest) {
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

    shape->upperLeft.x += vertex.x;
    shape->upperLeft.y += vertex.y;
    shape->lowerRight.x += vertex.x;
    shape->lowerRight.y += vertex.y;
    shape->center.x += vertex.x;
    shape->center.y += vertex.y;
}

void normalizeShapeOffset(Shape *shape, const Vertex vertex) {
    for (int i = 0; i < shape->polygonCount; ++i) {
        Polygon *polygon = &(shape->polygons[i]);
        for (int j = 0; j < polygon->vertexCount; ++j) {
            polygon->vertices[j].x -= vertex.x;
            polygon->vertices[j].y -= vertex.y;
        }
    }

    shape->upperLeft.x -= vertex.x;
    shape->upperLeft.y -= vertex.y;
    shape->lowerRight.x -= vertex.x;
    shape->lowerRight.y -= vertex.y;
    shape->center.x -= vertex.x;
    shape->center.y -= vertex.y;
}

void scaleVertex(Vertex *v, float scale, Vertex pivot) {
    Vertex temp = (Vertex){round((v->x - pivot.x) * scale + pivot.x),
                           round((v->y - pivot.y) * scale + pivot.y)};
    *v = (Vertex){temp.x, temp.y};
}

void scaleShape(Shape *shape, float scale, Vertex pivot) {
    for (int i = 0; i < shape->polygonCount; ++i) {
        Polygon *polygon = &(shape->polygons[i]);
        for (int j = 0; j < polygon->vertexCount; ++j) {
            scaleVertex(&(polygon->vertices[j]), scale, pivot);
        }
    }

    scaleVertex(&(shape->upperLeft), scale, pivot);
    scaleVertex(&(shape->lowerRight), scale, pivot);
    scaleVertex(&(shape->center), scale, pivot);
}

void calculateShapeBoundaries(Shape *shape) {
    int xMin = shape->polygons[0].vertices[0].x;
    int yMin = shape->polygons[0].vertices[0].y;
    int xMax = xMin;
    int yMax = yMin;

    for (int i = 0; i < shape->polygonCount; ++i) {
        Polygon *p = &(shape->polygons[i]);
        for (int j = 0; j < p->vertexCount; ++j) {
            Vertex *v = &(p->vertices[j]);

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

    shape->upperLeft = (Vertex){xMin, yMin};
    shape->lowerRight = (Vertex){xMax, yMax};
}

void calculateShapeCenter(Shape *shape) {
    shape->center =
        (Vertex){round((shape->upperLeft.x + shape->lowerRight.x) / 2),
                 round((shape->upperLeft.y + shape->lowerRight.y) / 2)};
}

void prepareShapeForRotation(Shape *shape, Vertex pivot) {
    calculateShapeBoundaries(shape);
    calculateShapeCenter(shape);

    int radius = max(
        max(round(distance(shape->upperLeft, pivot)),
            round(distance((Vertex){shape->upperLeft.x, shape->lowerRight.y},
                           pivot))),
        max(round(distance(shape->lowerRight, pivot)),
            round(distance((Vertex){shape->lowerRight.x, shape->upperLeft.y},
                           pivot))));

    Vertex offset = (Vertex){radius - pivot.x + shape->upperLeft.x,
                             radius - pivot.y + shape->upperLeft.y};

    offsetShape(shape, offset);
    calculateShapeBoundaries(shape);
}

void rotateShape(Shape *shape, const int degrees, Vertex pivot) {
    const float radians = degrees * M_PI / 180;
    const float sin = sinf(radians);
    const float cos = cosf(radians);
    const Vertex *offset = &pivot;

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
    calculateShapeBoundaries(shape);
}

int isCritical(Vertex a, Vertex b, Vertex c) {
    return (a.y < b.y && c.y < b.y) || (a.y > b.y && c.y > b.y);
}

float distance(Vertex a, Vertex b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}
