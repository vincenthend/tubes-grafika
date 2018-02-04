#include "color.h"

void initColor(Color *c, char *color) {
    int hexcol = strtol(color, NULL, 16);

    (*c).r = hexcol >> 16;
    (*c).g = (hexcol - (hexcol >> 16 << 16)) >> 8;
    (*c).b = (hexcol - (hexcol >> 8 << 8));
    (*c).a = 0;
}

char isSameColor(Color c1, Color c2) {
    return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a);
}
