#include "rasterfont.h"

void initRasterFont(RasterFont *rf) {
    rf->dict = (Shape *)malloc(256 * sizeof(Shape));
    rf->height = 90;
    rf->width = 110;
}

void openRasterFont(char *ch, RasterFont *rf) {
    for (int i = 'a'; i <= 'z'; i++) {
        initShape(&(rf->dict[i]), 10);
        for (int j = 0; j < 10; j++) {
            initPolygon(&(rf->dict[i].polygons[j]), 20);
        }
    }

    char filename[30];
    strcpy(filename, "fonts/");
    strcat(filename, ch);
    strcat(filename, ".txt");

    char char_dump[2];
    FILE *file;
    file = fopen(filename, "r");
    if (file) {
        fscanf(file, "%d", &(rf->width));
        fscanf(file, "%d", &(rf->height));

        int x, y;
        while (fscanf(file, "%s", char_dump) == 1) {
            // Let the party begin
            // Check for -1,-1 which means new polygon
            // Check for -9,-9 which means new char
            // Check for -999,-999 which means end of file

            int c = char_dump[0];

            int polygonIndex = 0;
            int vertexIndex = 0;
            while (fscanf(file, "%d,%d", &x, &y) == 2) {
                if ((x == -999 && y == -999) || (x == -9 && y == -9)) {
                    rf->dict[c].polygons[polygonIndex].vertexCount =
                        vertexIndex;
                    rf->dict[c].polygonCount = polygonIndex + 1;

                    break;
                } else if (x == -1 && y == -1) {
                    rf->dict[c].polygons[polygonIndex].vertexCount =
                        vertexIndex;

                    polygonIndex++;
                    vertexIndex = 0;
                } else {
                    rf->dict[c].polygons[polygonIndex].vertices[vertexIndex].x =
                        x;
                    rf->dict[c].polygons[polygonIndex].vertices[vertexIndex].y =
                        y;

                    vertexIndex++;
                }
            }
        }
    }

    fclose(file);
}
