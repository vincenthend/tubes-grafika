#include "color.h"

void initColor(Color *color, char *colorHex) {
    int colorHexDecimal = strtol(colorHex, NULL, 16);

    color->r = colorHexDecimal >> 16;
    color->g = (colorHexDecimal - (colorHexDecimal >> 16 << 16)) >> 8;
    color->b = (colorHexDecimal - (colorHexDecimal >> 8 << 8));
    color->a = 0;
}

char isSameColor(Color color1, Color color2) {
    return (color1.r == color2.r && color1.g == color2.g &&
            color1.b == color2.b && color1.a == color2.a);
}

void cloneColor(const Color *src, Color *dest) {
	dest = (Color *) malloc(sizeof(Color));

	dest->r = src->r;
	dest->g = src->g;
	dest->b = src->b;
	dest->a = src->a;
}