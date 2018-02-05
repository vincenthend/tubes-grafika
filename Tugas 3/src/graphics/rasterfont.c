#include "rasterfont.h"

void initRasterFont(RasterFont *rasterFont) {
    rasterFont->dict = (Shape *)malloc(256 * sizeof(Shape));
    rasterFont->height = 90;
    rasterFont->width = 110;
}

void openRasterFont(char *rasterFont, RasterFont *rf) {
    // TODO: Put some malloc here for Shapes and Polygons
    for (int i = 'a'; i <= 'z'; i++) {
        initShape(&(rf->dict[i]), 10);
        for (int j = 0; j < 10; j++) {
            initPolygon(&(rf->dict[i].polygons[j]), 20);
        }
    }

    char rasterFontFilename[30];
    strcpy(rasterFontFilename, "fonts/");
    strcat(rasterFontFilename, rasterFont);
    strcat(rasterFontFilename, ".txt");

    char charDump[2];
    FILE *rasterFontFile;
    rasterFontFile = fopen(rasterFontFilename, "r");
    if (rasterFontFile) {
        fscanf(rasterFontFile, "%d", &((*rf).width));
        fscanf(rasterFontFile, "%d", &((*rf).height));

        int x, y;
        while (fscanf(rasterFontFile, "%s", charDump) == 1) {
            // Let the party begin
            // Check for -1,-1 which means new polygon
            // Check for -9,-9 which means new char
            // Check for -999,-999 which means end of file

            // printf("Char dump: %s\n", charDump);

            int currentChar = charDump[0];

            int polygonIndex = 0;
            int verticeIndex = 0;
            while (fscanf(rasterFontFile, "%d,%d", &x, &y) == 2) {
                // printf("Integers read: (%d,%d)\n", x, y);

                if ((x == -999 && y == -999) || (x == -9 && y == -9)) {
                    (*rf).dict[currentChar].polygons[polygonIndex].count =
                        verticeIndex;
                    (*rf).dict[currentChar].count = polygonIndex + 1;

                    // printf(
                    //     "Vertices count: %d\n",
                    //     (*rf).dict[currentChar].polygons[polygonIndex].count);
                    // printf("Polygons count: %d\n",
                    //        (*rf).dict[currentChar].count);

                    break;
                } else if (x == -1 && y == -1) {
                    (*rf).dict[currentChar].polygons[polygonIndex].count =
                        verticeIndex;

                    polygonIndex++;
                    verticeIndex = 0;
                } else {
                    // Normal read
                    (*rf)
                        .dict[currentChar]
                        .polygons[polygonIndex]
                        .vertices[verticeIndex]
                        .x = x;
                    (*rf)
                        .dict[currentChar]
                        .polygons[polygonIndex]
                        .vertices[verticeIndex]
                        .y = y;

                    verticeIndex++;
                }
            }
        }
    }

    fclose(rasterFontFile);
}
