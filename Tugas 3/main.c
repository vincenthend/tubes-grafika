#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "src/color.h"
#include "src/drawer.h"
#include "src/framebuffer.h"
#include "src/graphics/font.h"
#include "src/graphics/image.h"
#include "src/graphics/rasterfont.h"
#include "src/graphics/shape.h"
#include "src/printer.h"
#include "src/rasterizer.h"

int main() {
    FrameBuffer fb = initFrameBuffer();

    // Initialization
    Color white, black, grey, pink, background;
    Color orange, yellow, green;

    initColor(&orange, "FF7800");
    initColor(&yellow, "FFFF00");
    initColor(&green, "00FF00");
    initColor(&white, "FFFFFF");
    initColor(&black, "000000");
    initColor(&grey, "77797A");
    initColor(&pink, "FF8AD1");
    initColor(&background, "0D1B46");

    // RasterFont rasterFont;
    // initRasterFont(&rasterFont);
    // openRasterFont("raster_font", &rasterFont);

    drawLine(&fb, 400, 400, 100, 1000, pink);

    // int i, j;
    // for(i = 0; i < 1; i++) {
    //     for (j = 0; j < 5; j++) {
    //         printf("(%d,%d)\n", rasterFont.dict['z'].polygons[i].vertices[j].x, rasterFont.dict['z'].polygons[i].vertices[j].y);
    //     }
    // }

    // Vertex v;
    // v.x = 5;
    // v.y = 10;

    // fillChar(&fb, 'a', &rasterFont, v, pink);

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
