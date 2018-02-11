#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

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
    VectorImage plane;
    VectorImage blade_left;
    VectorImage blade_right;
    openVectorImage("plane_vector", &plane);
    openVectorImage("blade_left", &blade_left);
    openVectorImage("blade_right", &blade_right);
    // Draw and fill
    Vertex v;
    v.x = 0;
    v.y = 0;

    int deg = 5;
    
    clock_t start;
    clock_t end;
    double renderTime;

    int correction = 5;

    while(1){        
        start = clock();
        
        // clearScreen(&fb);
        calculateVectorImageBoundaries(&blade_left);
        blade_left.upperLeft.x += v.x - correction;
        blade_left.lowerRight.x += v.x + correction;
        blade_left.upperLeft.y - correction;
        blade_left.lowerRight.y += v.y + correction;

        calculateVectorImageBoundaries(&blade_right);
        blade_right.upperLeft.x += v.x - correction;
        blade_right.lowerRight.x += v.x + correction;
        blade_right.upperLeft.y - correction;
        blade_right.lowerRight.y += v.y + correction;

        clearArea(&fb, blade_left.upperLeft, blade_left.lowerRight);
        clearArea(&fb, blade_right.upperLeft, blade_right.lowerRight);

        fillImage(&fb, &plane, v);
        fillImage(&fb, &blade_left, v);
        fillImage(&fb, &blade_right, v);
        rotateVectorImage(&blade_left, deg);
        rotateVectorImage(&blade_right, deg);
        end = clock();

        deg += 5;
        //66000 for 30fps
        renderTime = 33000 - ((double)(end-start))/CLOCKS_PER_SEC;
        if(renderTime > 0){
            usleep(renderTime);
        }
    }

    updateFrame(&fb);

    return 0;
}
