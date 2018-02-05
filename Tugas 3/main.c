#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "color.h"
#include "drawer.h"
#include "framebuffer.h"
#include "graphics.h"
#include "printer.h"
#include "rasterizer.h"

FrameBuffer fb;
void drawRainbow(FrameBuffer *fb, int x, int y) {
    Color red, orange, yellow, green, blue, purple;
    initColor(&red, "FF0000");
    initColor(&orange, "FF7700");
    initColor(&yellow, "FFFF00");
    initColor(&green, "009900");
    initColor(&blue, "000099");
    initColor(&purple, "990099");

    fillSquareArea(fb, x - 8, y + 4, x + 20, y + 6, red);
    fillSquareArea(fb, x - 8, y + 7, x + 20, y + 9, orange);
    fillSquareArea(fb, x - 8, y + 10, x + 20, y + 12, yellow);
    fillSquareArea(fb, x - 8, y + 13, x + 20, y + 15, green);
    fillSquareArea(fb, x - 8, y + 16, x + 20, y + 18, blue);
    fillSquareArea(fb, x - 8, y + 19, x + 20, y + 21, purple);
}

int main() {
    fb = initialize();

    //Initialization
    Color white, black, grey, pink, background;
    Color orange, yellow, green;

    initColor(&orange, "ff7800");
    initColor(&yellow, "FFFF00");
    initColor(&green, "00ff00");
    initColor(&white, "FFFFFF");
    initColor(&black, "000000");
    initColor(&grey, "77797A");
    initColor(&pink, "FF8AD1");
    initColor(&background, "0d1b46");

    RasterFont rasterFont;
    initRasterFont(&rasterFont);
    openRasterFont("raster_font", &rasterFont);

    // int i, j;
    // for(i = 0; i < 1; i++) {
    //     for (j = 0; j < 5; j++) {
    //         printf("(%d,%d)\n", rasterFont.dict['z'].polygons[i].vertices[j].x, rasterFont.dict['z'].polygons[i].vertices[j].y);
    //     }
    // }

    Vertex v;
    v.x = 5;
    v.y = 10;

    fillChar(&fb, "a", &rasterFont, v, pink);

    // for (char i = 'a'; i <= 'z'; i++) {
    //     fillChar(&fb, i, &rasterFont, v, pink);
    //     v.x += 100;
    //     if (v.x >= 1000) {
    //         v.y += 120;
    //         v.x = 5;
    //     }
    // }
    return 0;
}
