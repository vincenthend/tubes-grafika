#ifndef _COLOR_H
#define _COLOR_H

#include <stdlib.h>

typedef struct {
    int r;
    int g;
    int b;
    int a;
} Color;

void initColor(Color *c, char *color);

char isSameColor(Color c1, Color c2);
#endif
