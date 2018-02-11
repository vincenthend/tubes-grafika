#ifndef _VECTORIMAGE_H
#define _VECTORIMAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shape.h"
#include "../color.h"

/**
 * File VectorImage
 * digunakan untuk membuka gambar bit map
 */

typedef struct {
    Shape *shape;
    Color *color;
    int height;
    int width;
    int n_component;
    Vertex upperLeft;
    Vertex lowerRight;
    Vertex center;
} VectorImage;

void openVectorImage(char *imageName, VectorImage *image);

void rotateVectorImage(VectorImage *image, int degrees);

void calculateVectorImageCenter(VectorImage *image);

void calculateVectorImageBoundaries(VectorImage *image);

#endif
