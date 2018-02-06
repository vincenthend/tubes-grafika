#include "image.h"

void openImage(char *imageName, Image *image) {
    char imageFilename[30];
    strcpy(imageFilename, "image/");
    strcat(imageFilename, imageName);
    strcat(imageFilename, ".txt");

    FILE *imageFile;
    imageFile = fopen(imageFilename, "r");
    if (imageFile) {
        fscanf(imageFile, "%d", &(image->width));
        fscanf(imageFile, "%d", &(image->height));
        image->data = (char *)malloc(image->width * image->height + 2);

        if (fscanf(imageFile, "%s", image->data) == 1) {
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
