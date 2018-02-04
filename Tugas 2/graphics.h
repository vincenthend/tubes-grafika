#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *dict[256];
    int height;
    int width;
} Font;

typedef struct {
    char *data;
    int height;
    int width;
} Image;

void openFont(char *font, Font *f);

void openImage(char *image, Image *i);

#endif
