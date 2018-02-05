#include "graphics.h"

void openFont(char *fontChar, Font *font) {
    for (int i = 0; i < 256; i++) {
        (*font).dict[i] = (char *)malloc(100);
    }

    int c = 'a';
    char fontFilename[30];
    strcpy(fontFilename, "fonts/");
    strcat(fontFilename, fontChar);
    strcat(fontFilename, ".txt");

    FILE *fontFile;
    fontFile = fopen(fontFilename, "r");
    if (fontFile) {
        fscanf(fontFile, "%d", &((*font).width));
        fscanf(fontFile, "%d", &((*font).height));
        while ((fscanf(fontFile, "%s", (*font).dict[c]) == 1) && (c <= 'z')) {
            c++;
        }

        if (c == 'z' + 1) {
            printf("Successfully loaded font %s\n", fontChar);
        } else {
            printf("Error in reading font %s\n", fontChar);
        }
        fclose(fontFile);
    } else {
        printf("Font does not exist\n");
        exit(5);
    }
}

void openImage(char *imageName, Image *image) {
    char imageFilename[30];
    strcpy(imageFilename, "image/");
    strcat(imageFilename, imageName);
    strcat(imageFilename, ".txt");

    FILE *imageFile;
    imageFile = fopen(imageFilename, "r");
    if (imageFile) {
        fscanf(imageFile, "%d", &((*image).width));
        fscanf(imageFile, "%d", &((*image).height));
        (*image).data = (char *)malloc((*image).width * (*image).height + 2);

        if (fscanf(imageFile, "%s", (*image).data) == 1) {
            printf("Successfully loaded image %s\n", imageName);
        } else {
            printf("Error in reading image %s\n", imageName);
        }
        fclose(imageFile);
    } else {
        printf("Image does not exist\n");
        exit(5);
    }
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

    char *ch_dump;
    FILE *rasterFontFile;
    rasterFontFile = fopen(rasterFontFilename, "r");
    if (rasterFontFile) {
        fscanf(rasterFontFile, "%d", &((*rf).width));
        fscanf(rasterFontFile, "%d", &((*rf).height));

        int x, y;
        int current_char = 'a';
        while (fscanf(rasterFontFile, "%s", ch_dump) == 1) {
            // Let the party begin
            // Check for -1,-1 which means new polygon
            // Check for -9,-9 which means new char
            // Check for -999,-999 which means end of file
            int poly_index = 0;
            int vertice_index = 0;
            printf("ch_dump: %s\n", ch_dump);
            // printf("current_char: %d\n", current_char);
            while (fscanf(rasterFontFile, "%d,%d", &x, &y) == 2) {
                // printf("(%d,%d)\n", x, y);
                if ((x == -999 && y == -999) || (x == -9 && y == -9)) {
                    (*rf).dict[current_char].polygons[poly_index].count =
                        vertice_index;
                    (*rf).dict[current_char].count = poly_index + 1;
                    // printf("vertices.count: %d\n", (*rf).dict[current_char].polygons[poly_index].count);
                    // printf("polygons.count: %d\n", (*rf).dict[current_char].count);
                    current_char++;
                    break;
                } else {
                    if (x == -1 && y == -1) {
                        (*rf).dict[current_char].polygons[poly_index].count =
                            vertice_index;
                        poly_index++;
                        vertice_index = 0;
                    } else {
                        // Normal read
                        (*rf)
                            .dict[current_char]
                            .polygons[poly_index]
                            .vertices[vertice_index]
                            .x = x;
                        (*rf)
                            .dict[current_char]
                            .polygons[poly_index]
                            .vertices[vertice_index]
                            .y = y;
                        vertice_index++;
                    }
                }
            }
        }
        fclose(rasterFontFile);
    }
}
