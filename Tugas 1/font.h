#ifndef _FONT_H
#define _FONT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *dict[256];
    int height;
    int width;
} Font;

void openFont(char *font, Font *f);

#endif
