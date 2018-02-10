#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "src/color.h"
#include "src/drawer.h"
#include "src/framebuffer.h"
#include "src/graphics/font.h"
#include "src/graphics/image.h"
#include "src/graphics/vectorimage.h"
#include "src/graphics/rasterfont.h"
#include "src/graphics/shape.h"
#include "src/printer.h"
#include "src/rasterizer.h"

int main() {
    FrameBuffer fb = initFrameBuffer();
    
    // Load Image
    VectorImage image;
    openVectorImage("plane_vector", &image);
    // Draw and fill
    Vertex v;
    v.x = 300;
    v.y = 100;

    //system("clear");
    fillImage(&fb, &image);

    updateFrame(&fb);

    sleep(3);

    return 0;
}
