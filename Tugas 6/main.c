#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>


#include "src/color.h"
#include "src/drawer.h"
#include "src/framebuffer.h"
#include "src/graphics/clipping.h"
#include "src/graphics/font.h"
#include "src/graphics/image.h"
#include "src/graphics/rasterfont.h"
#include "src/graphics/shape.h"
#include "src/graphics/vectorimage.h"
#include "src/printer.h"
#include "src/rasterizer.h"


static struct termios old, new;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); 
  new = old;
  new.c_lflag &= ~ICANON;
  new.c_lflag &= echo ? ECHO : ~ECHO;
  tcsetattr(0, TCSANOW, &new);
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}


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

    Clipper clipper;
    Vertex startingVertex, endingVertex;
    startingVertex.x = 300;
    startingVertex.y = 300;
    endingVertex.x = 1000;
    endingVertex.y = 1000;
    
    Color yellow;
    initColor(&yellow, "FFF000");

    while (1) {
        VectorImage plane2, blade_left2, blade_right2;
        cloneVectorImage(&plane, &plane2);
        cloneVectorImage(&blade_left, &blade_left2);
        cloneVectorImage(&blade_right, &blade_right2);

        // clearArea(&fb, startingVertex, endingVertex);
        system("clear");

        initSquareClipper(&clipper, startingVertex.x, startingVertex.y,
                      endingVertex.x, endingVertex.y);
        drawSquare(&fb, startingVertex.x, startingVertex.y, endingVertex.x,
                   endingVertex.y, yellow);

        clipVectorImage(&plane2, clipper);
        clipVectorImage(&blade_left2, clipper);
        clipVectorImage(&blade_right2, clipper);

        fillImage(&fb, &plane2, v);
        fillImage(&fb, &blade_left2, v);
        fillImage(&fb, &blade_right2, v);

        if (getch() == '\033') {
            getch();
            switch(getch()) {
                case 'A':
                    // code for arrow up
                    startingVertex.y -= 10;
                    endingVertex.y -= 10;
                    break;
                case 'B':
                    // code for arrow down
                    startingVertex.y += 10;
                    endingVertex.y += 10;
                    break;
                case 'C':
                    // code for arrow right
                    startingVertex.x += 10;
                    endingVertex.x += 10;
                    break;
                case 'D':
                    // code for arrow left
                    startingVertex.x -= 10;
                    endingVertex.x -= 10;
                    break;
            }
        }
    }

    updateFrame(&fb);

    return 0;
}
