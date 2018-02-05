#ifndef _FONT_H
#define _FONT_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    char *dict[256];
    int height;
    int width;
} Font;

void openFont(char *fontChar, Font *font);

#endif
