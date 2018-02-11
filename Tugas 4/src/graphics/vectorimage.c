#include "vectorimage.h"



#define MAX_POLYGONS 10
#define MAX_VERTICES 30

void openVectorImage(char *imageName, VectorImage *image){
    char filename[30];
    Color *c;

    strcpy(filename, "image/");
    strcat(filename, imageName);
    strcat(filename, ".txt");

    FILE *file;
    file = fopen(filename, "r");
    if (file) {
        // Read File
        int n_comp;
        fscanf(file, "%d", &(image->width));
        fscanf(file, "%d", &(image->height));
        fscanf(file, "%d", &n_comp);
        (*image).n_component = n_comp;

        // Initialize list of shapes and color
        image->shape = (Shape *)malloc(n_comp * sizeof(Shape));
        image->color = (Color *)malloc(n_comp * sizeof(Color));

        for (int i = 0; i < n_comp; i++){
            initShape(&(image->shape[i]), MAX_POLYGONS);
            for (int j = 0; j < MAX_POLYGONS; j++) {
                initPolygon(&(image->shape[i].polygons[j]), MAX_VERTICES);
            }
        }

        // Format : color, polygon, separator, polygon etc.
        // -1, -1 means separator for new polygon
        // -9, -9 means new shape

        char polyColor[7];
        int x, y;
        for (int n = 0; n < image->n_component; n++) {
            Shape* s = &(image->shape[n]);
            fscanf(file, "%s", polyColor);
            int polygonIndex = 0;
            int vertexIndex = 0;
            do {
                fscanf(file, "%d, %d", &x, &y);
                if (x == -1 && y == -1) {
                    s->polygons[polygonIndex].vertexCount = vertexIndex;
                    polygonIndex++;
                    vertexIndex = 0;
                } else if (x >= 0 && y >= 0) {
                    s->polygons[polygonIndex].vertices[vertexIndex] = (Vertex) {x, y};
                    vertexIndex++;
                }
            } while(x != -9 && y != -9);
            s->polygons[polygonIndex].vertexCount = vertexIndex;
            s->polygonCount = polygonIndex + 1;
            initColor(&(image->color[n]), polyColor);
        }
        calculateVectorImageBoundaries(image);
        calculateVectorImageCenter(image);
        fclose(file);
    } else {
        printf("Image does not exist\n");
        exit(5);
    }
}

void rotateVectorImage(VectorImage *image, int degrees){
    int i;
    for (i = 0; i < image->n_component; i++) {
        rotateShape(&(image->shape[i]), degrees, image->center);
    }
}

void calculateVectorImageBoundaries(VectorImage *image) {
    Shape *shape = &(image->shape[0]);
    int xMin = shape->polygons[0].vertices[0].x;
    int yMin = shape->polygons[0].vertices[0].y;
    int xMax = xMin;
    int yMax = yMin;

    for (int i = 0; i< image->n_component; i++){
        shape = &(image->shape[i]);

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
    }

    image->upperLeft = (Vertex) { xMin, yMin };
    image->lowerRight = (Vertex) { xMax, yMax };
}

void calculateVectorImageCenter(VectorImage *image) {
    image->center = (Vertex) {
        round((image->upperLeft.x + image->lowerRight.x) / 2),
        round((image->upperLeft.y + image->lowerRight.y) / 2)
    };
}