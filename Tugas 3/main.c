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

    // Shape s;
    // initShape(&s, 2);

    // initPolygon(&(s.polygons[0]), 5);
    // s.polygons[0].vertices[0].x = 700;
    // s.polygons[0].vertices[0].y = 100;
    // s.polygons[0].vertices[1].x = 900;
    // s.polygons[0].vertices[1].y = 100;
    // s.polygons[0].vertices[2].x = 1000;
    // s.polygons[0].vertices[2].y = 300;
    // s.polygons[0].vertices[3].x = 800;
    // s.polygons[0].vertices[3].y = 600;
    // s.polygons[0].vertices[4].x = 600;
    // s.polygons[0].vertices[4].y = 300;

    // initPolygon(&(s.polygons[1]), 3);
    // s.polygons[1].vertices[0].x = 750;
    // s.polygons[1].vertices[0].y = 200;
    // s.polygons[1].vertices[1].x = 850;
    // s.polygons[1].vertices[1].y = 200;
    // s.polygons[1].vertices[2].x = 800;
    // s.polygons[1].vertices[2].y = 400;

    RasterFont *rasterFont;
    initRasterFont(rasterFont);
    openRasterFont("raster_font", rasterFont);

    // Vertex v;
    // v.x = 5;
    // v.y = 10;
    // for (char i = 'a'; i <= 'z'; i++) {
    //     fillChar(&fb, i, rasterFont, v, pink);
    // }
    return 0;
}
