#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "src/color.h"
#include "src/drawer.h"
#include "src/framebuffer.h"
#include "src/graphics/font.h"
#include "src/graphics/image.h"
#include "src/graphics/rasterfont.h"
#include "src/graphics/shape.h"
#include "src/graphics/vectorimage.h"
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

    calculateVectorImageBoundaries(&plane);
    calculateVectorImageCenter(&plane);

    calculateVectorImageBoundaries(&blade_left);
    calculateVectorImageCenter(&blade_left);

    calculateVectorImageBoundaries(&blade_right);
    calculateVectorImageCenter(&blade_right);

    system("clear");

    float scale = 1;
    while (1) {
        start = clock();

        VectorImage plane2, blade_left2, blade_right2;
        cloneVectorImage(&plane, &plane2);
        cloneVectorImage(&blade_left, &blade_left2);
        cloneVectorImage(&blade_right, &blade_right2);

        blade_left2.upperLeft.x += v.x - correction;
        blade_left2.lowerRight.x += v.x + correction;
        blade_left2.upperLeft.y += v.y - correction;
        blade_left2.lowerRight.y += v.y + correction;

        blade_right2.upperLeft.x += v.x - correction;
        blade_right2.lowerRight.x += v.x + correction;
        blade_right2.upperLeft.y += v.y - correction;
        blade_right2.lowerRight.y += v.y + correction;

        rotateVectorImage(&blade_left2, deg);
        rotateVectorImage(&blade_right2, deg);

        scaleVectorImage(&plane2, scale, plane2.center);
        scaleVectorImage(&blade_left2, scale, plane2.center);
        scaleVectorImage(&blade_right2, scale, plane2.center);

        clearArea(&fb, plane2.upperLeft, plane2.lowerRight);

        fillImage(&fb, &plane2, v);
        fillImage(&fb, &blade_left2, v);
        fillImage(&fb, &blade_right2, v);

        end = clock();

        // 66000 for 30fps
        renderTime = 66000 - ((double)(end - start)) / CLOCKS_PER_SEC;
        if (renderTime > 0) {
            usleep(renderTime);
        }

        deg += 30;
        scale += 0.1;
    }

    updateFrame(&fb);

    return 0;
}
