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
    VectorImage itb_gedung;
    VectorImage itb_jalan;

    openVectorImage("petaITB", &itb_gedung);
    printf("Gedung OK\n");
    openVectorImage("jalan", &itb_jalan);
    printf("Jalan\n");

    // Draw and fill
    Vertex v;
    v.x = 0;
    v.y = 0;

    Vertex offset;
    offset.x = 0;
    offset.y = 0;

    int deg = 5;

    clock_t start;
    clock_t end;
    double renderTime;

    int correction = 5;

    calculateVectorImageBoundaries(&itb_gedung);
    calculateVectorImageCenter(&itb_gedung);

    calculateVectorImageBoundaries(&itb_jalan);
    calculateVectorImageCenter(&itb_jalan);

    float scale = 1;

    Clipper clipper;
    Vertex startingVertex, endingVertex;
    startingVertex.x = 300;
    startingVertex.y = 300;
    endingVertex.x = 1000;
    endingVertex.y = 1000;
    
    Color yellow;
    initColor(&yellow, "FFF000");

    VectorImage itb_gedung2, itb_jalan2;

    // scaleVectorImage(VectorImage &itb_gedung2, scale, Vertex pivot);
    
    while (1) {
        cloneVectorImage(&itb_gedung, &itb_gedung2);
        cloneVectorImage(&itb_jalan, &itb_jalan2);
        system("clear");

        for (int i = 0; i < itb_gedung2.n_component; i++) {
            offsetShape(&(itb_gedung2.shape[i]), offset);
        }
        for (int i = 0; i < itb_jalan2.n_component; i++) {
            offsetShape(&(itb_jalan2.shape[i]), offset);
        }

        initSquareClipper(&clipper, startingVertex.x, startingVertex.y,
                      endingVertex.x, endingVertex.y);
        drawSquare(&fb, startingVertex.x, startingVertex.y, endingVertex.x,
                   endingVertex.y, yellow);

        clipVectorImage(&itb_gedung2, clipper);
        clipVectorImage(&itb_jalan2, clipper);

        fillImage(&fb, &itb_gedung2, v);
        fillImage(&fb, &itb_jalan2, v);

        if (getch() == '\033') {
            getch();
            switch(getch()) {
                case 'A':
                    // code for arrow up
                    offset.y += 10;
                    break;
                case 'B':
                    // code for arrow down
                    offset.y -= 10;
                    break;
                case 'C':
                    offset.x -= 10;
                    // code for arrow right
                    break;
                case 'D':
                    // code for arrow left
                    offset.x += 10;
                    break;
            }
        }
    }

    updateFrame(&fb);

    return 0;
}
