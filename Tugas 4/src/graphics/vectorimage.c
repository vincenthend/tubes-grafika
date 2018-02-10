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

        for(int i = 0; i < n_comp; i++){
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
        for(int n = 0; n < image->n_component; n++){            
            fscanf(file, "%s", polyColor);
            printf("%s\n",polyColor);
            int polygonIndex = 0;
            int vertexIndex = 0;
            do{
                fscanf(file, "%d, %d", &x, &y);
                if(x == -1 && y == -1) {
                    image->shape[n].polygons[polygonIndex].vertexCount = vertexIndex;
                    polygonIndex++;
                    vertexIndex = 0;
                }
                else if (x >= 0 && y >= 0) {
                    image->shape[n].polygons[polygonIndex].vertices[vertexIndex].x = x;
                    image->shape[n].polygons[polygonIndex].vertices[vertexIndex].y = y;
                    vertexIndex++;
                }
                
            }while(x != -9 && y != -9);
            image->shape[n].polygons[polygonIndex].vertexCount = vertexIndex;
            image->shape[n].polygonCount = polygonIndex + 1;
            initColor(&(image->color[n]), polyColor);
        }

        fclose(file);
    } else {
        printf("Image does not exist\n");
        exit(5);
    }
}