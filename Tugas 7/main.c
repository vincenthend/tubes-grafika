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

int initMouse(){
  int bytes; 
    const char *pDevice = "/dev/input/mice";
 
    // Open Mouse
    int mouse = open(pDevice, O_RDWR);
    if(mouse == -1)
    {
        printf("ERROR Opening %s\n", pDevice);
        return -1;
    }
}


int main() {
    FrameBuffer fb = initFrameBuffer();
    int bytes;
    int mouse = initMouse();
    unsigned char mouseState[3];
    int8_t x = 0;
    int8_t y = 0;
    int posX = 854;
    int posY = 384;

    while(1){
        bytes = read(mouse, mouseState, sizeof(mouseState));
        if(bytes > 0){
            // left = data[0] & 0x1;
            // right = data[0] & 0x2;
            // middle = data[0] & 0x4;
            // x = data[1];
            // y = data[2];

            x = mouseState[1];
            y = mouseState[2];
            posX += x;
            posY -= y;
            // printf("%d, %d\n",posY, posY);

            addPixelToBuffer(&fb, posX, posY, 255, 255, 255, 0);
        }
    }



    return 0;
}
