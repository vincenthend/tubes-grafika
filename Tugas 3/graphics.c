#include "graphics.h"

void openFont(char *font, Font *f) {
    int i;
    for (i = 0; i < 256; i++) {
        (*f).dict[i] = (char *)malloc(100);
    }

    int cidx = 'a';
    char font_filename[30];
    strcpy(font_filename, "fonts/");
    strcat(font_filename, font);
    strcat(font_filename, ".txt");

    FILE *font_file;
    font_file = fopen(font_filename, "r");
    if (font_file) {
        fscanf(font_file, "%d", &((*f).width));
        fscanf(font_file, "%d", &((*f).height));
        while ((fscanf(font_file, "%s", (*f).dict[cidx]) == 1) &&
               (cidx <= 'z')) {
            cidx++;
        }
        if (cidx == 'z' + 1) {
            printf("Successfully loaded font %s\n", font);
        } else {
            printf("Error in reading font %s\n", font);
        }
        fclose(font_file);
    } else {
        printf("Font does not exist\n");
        exit(5);
    }
}

void openImage(char *image, Image *img) {
    char image_filename[30];
    strcpy(image_filename, "image/");
    strcat(image_filename, image);
    strcat(image_filename, ".txt");

    FILE *image_file;
    image_file = fopen(image_filename, "r");
    if (image_file) {
        fscanf(image_file, "%d", &((*img).width));
        fscanf(image_file, "%d", &((*img).height));
        (*img).data = (char *)malloc((*img).width * (*img).height + 2);

        if (fscanf(image_file, "%s", (*img).data) == 1) {
            printf("Successfully loaded image %s\n", image);
        } else {
            printf("Error in reading image %s\n", image);
        }
        fclose(image_file);
    } else {
        printf("Image does not exist\n");
        exit(5);
    }
}

void openRasterFont(char *raster_font, RasterFont *rf) {
    // TODO: Put some malloc here for Shapes and Polygons
    for (int i = 'a'; i <= 'z'; i++) {
        initShape(&(rf->dict[i]), 10);
        for (int j = 0; j < 10; j++) {
            initPolygon(&(rf->dict[i].polygons[j]), 20);
        }
    }

    char rf_filename[30];
    strcpy(rf_filename, "fonts/");
    strcat(rf_filename, raster_font);
    strcat(rf_filename, ".txt");

    char *ch_dump;
    FILE *rf_file;
    rf_file = fopen(rf_filename, "r");
    if (rf_file) {
        fscanf(rf_file, "%d", &((*rf).width));
        fscanf(rf_file, "%d", &((*rf).height));

        int x, y;
        // Next line would be character
        int current_char = 'a';
        while (fscanf(rf_file, "%s", &ch_dump) == 1) {
            // Let the party begin
            // Check for -1,-1 which means new polygon
            // Check for -9,-9 which means new char
            // Check for -999,-999 which means end of file
            int poly_index = 0;
            int vertice_index = 0;
            char ch_dump_2;
            printf("ch_dump: %c\n", ch_dump);
            // printf("current_char: %d\n", current_char);
            while (fscanf(rf_file, "%d,%d", &x, &y) == 2) {
                // printf("(%d,%d)\n", x, y);
                if ((x == -999 && y == -999) || (x == -9 && y == -9)) {
                    (*rf).dict[current_char].polygons[poly_index].count =
                        vertice_index;
                    (*rf).dict[current_char].count = poly_index+1;
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
        fclose(rf_file);
    }
}
