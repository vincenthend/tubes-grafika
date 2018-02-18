#ifndef _COLOR_H
#define _COLOR_H

#include <stdlib.h>

/**
 * Kelas Color
 * Digunakan untuk menampung warna
 */

typedef struct {
    int r;
    int g;
    int b;
    int a;
} Color;

void initColor(Color *color, char *colorHex);

char isSameColor(Color color1, Color color2);

#endif
