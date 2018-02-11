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
    v.x = 300;
    v.y = 100;

    int deg = 5;
    
    clock_t start;
    clock_t end;
    double renderTime;

    int minMaxBL[4];
    int minMaxBR[4];
    int correction = 5;

    while(1){        
        start = clock();
        
        // clearScreen(&fb);
        findMinMaxVectorImage(&blade_left, &minMaxBL);
        minMaxBL[0] += v.x - correction;
        minMaxBL[1] += v.x + correction;
        minMaxBL[2] += v.y - correction;
        minMaxBL[3] += v.y + correction;

        findMinMaxVectorImage(&blade_right, &minMaxBR);
        minMaxBR[0] += v.x - correction;
        minMaxBR[1] += v.x + correction;
        minMaxBR[2] += v.y - correction;
        minMaxBR[3] += v.y + correction;

        areaClear(&fb, minMaxBL[0], minMaxBL[1], minMaxBL[2], minMaxBL[3]);
        areaClear(&fb, minMaxBR[0], minMaxBR[1], minMaxBR[2], minMaxBR[3]);

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
