#include "clipping.h"

void initSquareClipper(Clipper *clipper, int x0, int y0, int x1, int y1) {
    clipper->clipperSize = 4;
    clipper->clipperVertex =
        (Vertex *)malloc(clipper->clipperSize * sizeof(Vertex));
    clipper->clipperVertex[0].x = x0;
    clipper->clipperVertex[0].y = y0;
    clipper->clipperVertex[1].x = x0;
    clipper->clipperVertex[1].y = y1;
    clipper->clipperVertex[2].x = x1;
    clipper->clipperVertex[2].y = y1;
    clipper->clipperVertex[3].x = x1;
    clipper->clipperVertex[3].y = y0;
}

int countVertexInsideClip(Polygon *polygon, Vertex clip1, Vertex clip2) {
    int vertexCount = polygon->vertexCount;
    Vertex *endPoints = polygon->vertices;
    int counterVertexInsideClip = 0;

    //find vertex size that inside clipper
    for (int j = 0; j < vertexCount; j++) {
        //second end point vertex
        int k = (j + 1) % vertexCount;
        Vertex endPoint1 = endPoints[j];
        Vertex endPoint2 = endPoints[k];

        int firstPointPosition, secondPointPosition;

        firstPointPosition = (clip2.x - clip1.x) * (endPoint1.y - clip1.y) -
                             (clip2.y - clip1.y) * (endPoint1.x - clip1.x);
        secondPointPosition = (clip2.x - clip1.x) * (endPoint2.y - clip1.y) -
                              (clip2.y - clip1.y) * (endPoint2.x - clip1.x);

        if (firstPointPosition < 0 && secondPointPosition < 0) {
            counterVertexInsideClip++;
        } else if (firstPointPosition >= 0 && secondPointPosition < 0) {
            counterVertexInsideClip += 2;
        } else if (firstPointPosition < 0 && secondPointPosition >= 0) {
            counterVertexInsideClip++;
        }
    }

    return counterVertexInsideClip;
}

int countPolygonInsideClip(Shape *shapes, Vertex clip1, Vertex clip2) {
    int counterPolygonInsideClip = 0;

    for (int i = 0; i < shapes->polygonCount; i++) {
        int counterVertexInsideClip =
            countVertexInsideClip(&(shapes->polygons[i]), clip1, clip2);
        if (counterVertexInsideClip > 0) {
            counterPolygonInsideClip++;
        }
    }
    return counterPolygonInsideClip;
}

int countShapeInsideClip(VectorImage *image, Vertex clip1, Vertex clip2) {
    int counterShapeInsideClip = 0;

    for (int i = 0; i < image->n_component; i++) {
        int counterPolygonInsideClip =
            countPolygonInsideClip(&(image->shape[i]), clip1, clip2);
        if (counterPolygonInsideClip > 0) {
            counterShapeInsideClip++;
        }
    }
    return counterShapeInsideClip;
}

void clipVectorImageHelper(VectorImage *image, Vertex clip1, Vertex clip2) {
    VectorImage newVectorImage;
    newVectorImage.n_component = countShapeInsideClip(image, clip1, clip2);
    newVectorImage.height = image->height;
    newVectorImage.width = image->width;
    newVectorImage.shape =
        (Shape *)malloc(newVectorImage.n_component * sizeof(Shape));
    newVectorImage.color =
        (Color *)malloc(newVectorImage.n_component * sizeof(Color));

    int newShapeIterator = 0;

    //iterate all shape
    // printf("Shape Size: %d\n", newVectorImage.n_component);
    for (int shapeIterator = 0; shapeIterator < image->n_component;
         shapeIterator++) {

        int newPolygonSize = countPolygonInsideClip(
            &(image->shape[shapeIterator]), clip1, clip2);
        // printf("Polygon Size: %d\n", newPolygonSize);
        if (newPolygonSize == 0) {
            //do nothing
        } else {
            initShape(&(newVectorImage.shape[newShapeIterator]),
                      newPolygonSize);

            // cloneColor(&(image->color[shapeIterator]), (newVectorImage.color[newShapeIterator]));
            newVectorImage.color[newShapeIterator].r =
                image->color[shapeIterator].r;
            newVectorImage.color[newShapeIterator].g =
                image->color[shapeIterator].g;
            newVectorImage.color[newShapeIterator].b =
                image->color[shapeIterator].b;
            newVectorImage.color[newShapeIterator].a =
                image->color[shapeIterator].a;

            int newPolygonIterator = 0;

            int polygonCount = image->shape[shapeIterator].polygonCount;

            //iterate all polygon
            for (int i = 0; i < polygonCount; i++) {

                Polygon *polygons = image->shape[shapeIterator].polygons;
                int newVertexSize =
                    countVertexInsideClip(&(polygons[i]), clip1, clip2);
                // printf("Vertex Size: %d\n", newVertexSize);

                if (newVertexSize == 0) {
                    // do nothing
                } else {
                    int vertexCount =
                        image->shape[shapeIterator].polygons[i].vertexCount;
                    Vertex *endPoints =
                        image->shape[shapeIterator].polygons[i].vertices;

                    //create new polygon that are inside clipper
                    Polygon newPolygon;
                    initPolygon(&newPolygon, newVertexSize);
                    int newVertexIterator = 0;
                    for (int j = 0; j < vertexCount; j++) {
                        //second end point vertex
                        int k = (j + 1) % vertexCount;
                        Vertex endPoint1 = endPoints[j];
                        Vertex endPoint2 = endPoints[k];

                        int firstPointPosition, secondPointPosition;

                        firstPointPosition =
                            (clip2.x - clip1.x) * (endPoint1.y - clip1.y) -
                            (clip2.y - clip1.y) * (endPoint1.x - clip1.x);
                        secondPointPosition =
                            (clip2.x - clip1.x) * (endPoint2.y - clip1.y) -
                            (clip2.y - clip1.y) * (endPoint2.x - clip1.x);

                        if (firstPointPosition < 0 && secondPointPosition < 0) {
                            newPolygon.vertices[newVertexIterator].x =
                                endPoint2.x;
                            newPolygon.vertices[newVertexIterator].y =
                                endPoint2.y;
                            newVertexIterator++;
                        } else if (firstPointPosition >= 0 &&
                                   secondPointPosition < 0) {
                            newPolygon.vertices[newVertexIterator] =
                                findIntersect(clip1, clip2, endPoint1,
                                              endPoint2);
                            newVertexIterator++;

                            newPolygon.vertices[newVertexIterator].x =
                                endPoint2.x;
                            newPolygon.vertices[newVertexIterator].y =
                                endPoint2.y;
                            newVertexIterator++;
                        } else if (firstPointPosition < 0 &&
                                   secondPointPosition >= 0) {
                            newPolygon.vertices[newVertexIterator] =
                                findIntersect(clip1, clip2, endPoint1,
                                              endPoint2);
                            newVertexIterator++;
                        } else {
                            //do nothing
                        }
                    }

                    clonePolygon(&newPolygon,
                                 &newVectorImage.shape[newShapeIterator]
                                      .polygons[newPolygonIterator]);
                    newPolygonIterator++;
                }
            }

            newShapeIterator++;
        }
    }

    cloneVectorImage(&newVectorImage, image);
}

void clipVectorImage(VectorImage *image, Clipper clipper) {
    for (int i = 0; i < clipper.clipperSize; i++) {
        //second end point
        int secondEndPoint = (i + 1) % clipper.clipperSize;

        clipVectorImageHelper(image, clipper.clipperVertex[i],
                              clipper.clipperVertex[secondEndPoint]);
        // printf("Next Clip Orientation\n");
    }
    printf("HAHAHAH\n");
    for (int i = 0; i < image->n_component; i++) {
        printf("Shape %d:\n", i);
        for (int j = 0; j < image->shape[i].polygonCount; j++) {
            printf("Polygon %d:\n", j);
            for (int k = 0; k < image->shape[i].polygons[j].vertexCount; k++) {
                printf("Vertex %d:\n", k);
                printf("%d %d\n", image->shape[i].polygons[j].vertices[k].x,
                       image->shape[i].polygons[j].vertices[k].y);
                printf("%d %d %d\n", image->color[i].r, image->color[i].g,
                       image->color[i].b);
            }
        }
    }
    printf("YEYEYE\n");
}

Vertex findIntersect(Vertex line1, Vertex line2, Vertex line3, Vertex line4) {
    int numeratorX, denumeratorX;
    int numeratorY, denumeratorY;
    int x, y;
    Vertex result;

    //Find intersection point x
    numeratorX = (line1.x * line2.y - line1.y * line2.x) * (line3.x - line4.x) -
                 (line1.x - line2.x) * (line3.x * line4.y - line3.y * line4.x);
    denumeratorX = (line1.x - line2.x) * (line3.y - line4.y) -
                   (line1.y - line2.y) * (line3.x - line4.x);
    if (denumeratorX == 0 || numeratorX == 0) {
        x = 0;
    } else {
        x = numeratorX / denumeratorX;
    }

    //Find intersection point y
    numeratorY = (line1.x * line2.y - line1.y * line2.x) * (line3.y - line4.y) -
                 (line1.y - line2.y) * (line3.x * line4.y - line3.y * line4.x);
    denumeratorY = (line1.x - line2.x) * (line3.y - line4.y) -
                   (line1.y - line2.y) * (line3.x - line4.x);
    if (denumeratorY == 0 || numeratorY == 0) {
        y = 0;
    } else {
        y = numeratorY / denumeratorY;
    }

    result.x = x;
    result.y = y;
    return result;
}
