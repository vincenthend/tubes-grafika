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

    // Color initialization
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

    // Raster font initialization
    RasterFont rasterFont;
    initRasterFont(&rasterFont);
    openRasterFont("raster_font", &rasterFont);

    // Clear screen
    //printf("\e[1;1H\e[2J");

    // Draw and fill
    Vertex v;
    v.x = 500;
    v.y = 500;

    fillChar(&fb, 'd', &rasterFont, v, pink);

    sleep(3);

    return 0;
}
