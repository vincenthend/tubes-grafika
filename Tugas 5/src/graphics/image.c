#include "image.h"

void openImage(char *imageName, Image *image) {
    char filename[30];
    strcpy(filename, "images/");
    strcat(filename, imageName);
    strcat(filename, ".txt");

    FILE *file;
    file = fopen(filename, "r");
    if (file) {
        fscanf(file, "%d", &(image->width));
        fscanf(file, "%d", &(image->height));
        image->data = (char *)malloc(image->width * image->height + 2);

        if (fscanf(file, "%s", image->data) == 1) {
            printf("Successfully loaded image %s\n", imageName);
        } else {
            printf("Error in reading image %s\n", imageName);
        }
        fclose(file);
    } else {
        printf("Image does not exist\n");
        exit(5);
    }
}
