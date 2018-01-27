#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "framebuffer.h"
#include "drawer.h"
#include "printer.h"
#include "graphics.h"
#include "color.h"

FrameBuffer fb;
char* cdict [255];

int main(){
    int nyanX, nyanY, topLeftX, topLeftY, botRightX, botRightY;
    int x, y;
    fb = initialize();

    //Initialization
    Color c, black;
    Image nyanCat;

    initColor(&c, "FFFFFF");    
    initColor(&black, "000000");
    openImage("nyancat", &nyanCat);
    topLeftX = fb.screen_width - 810;
    topLeftY = fb.screen_height - 410;
    botRightX = fb.screen_width - 10;
    botRightY = fb.screen_height - 10;
    nyanX = botRightX - 50;
    nyanY = botRightY - 350;
    x = nyanX;
    y = nyanY;

    //Loop
    while(1){
        drawSquare(&fb, topLeftX, topLeftY,botRightX, botRightY, c);
        drawMonoImage(&fb, nyanCat, x, y, c);       

        x--;
        if(x < topLeftX) {
            fillSquareArea(&fb, x, y, nyanCat.width+x, nyanCat.height+y, black);
            x = nyanX;                        
        }   
        usleep(10000);
        fillSquareArea(&fb, x, y, nyanCat.width+x, nyanCat.height+y, black);
    }

    updateFrame(&fb);
    return 0;
}
