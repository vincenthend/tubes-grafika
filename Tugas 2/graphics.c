#include "graphics.h"

void openFont(char *font, Font *f) {
    int i;
    for (i = 0; i < 256; i++) {
        (*f).dict[i] = (char *)malloc(100);
    }

    int cidx = 'a';
    char image_filename[30];
    strcpy(image_filename, "fonts/");
    strcat(image_filename, font);
    strcat(image_filename, ".txt");

    FILE *image_file;
    image_file = fopen(image_filename, "r");
    if (image_file) {
        fscanf(image_file, "%d", &((*f).width));
        fscanf(image_file, "%d", &((*f).height));
        while ((fscanf(image_file, "%s", (*f).dict[cidx]) == 1) &&
               (cidx <= 'z')) {
            cidx++;
        }
        if (cidx == 'z' + 1) {
            printf("Successfully loaded font %s\n", font);
        } else {
            printf("Error in reading font %s\n", font);
        }
        fclose(image_file);
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
        printf("Font does not exist\n");
        exit(5);
    }
}
