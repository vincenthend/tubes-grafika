#include "color.h"

void initColor(Color *c, char *color) {
    int hexcol = strtol(color, NULL, 16);

    (*c).r = hexcol >> 16;
    (*c).g = (hexcol - (hexcol >> 16 << 16)) >> 8;
    (*c).b = (hexcol - (hexcol >> 8 << 8));
    (*c).a = 0;
}