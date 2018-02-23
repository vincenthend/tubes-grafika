#ifndef _IMAGE_H
#define _IMAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * File Image
 * digunakan untuk membuka gambar bit map
 */

typedef struct {
    char *data;
    int height;
    int width;
} Image;

void openImage(char *imageName, Image *image);

#endif
