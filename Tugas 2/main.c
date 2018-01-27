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
void drawRainbow(FrameBuffer* fb, int x , int y){
    Color red, orange, yellow, green, blue, purple;
    initColor(&red, "FF0000");
    initColor(&orange, "FF7700");
    initColor(&yellow, "FFFF00");
    initColor(&green, "009900");
    initColor(&blue, "000099");
    initColor(&purple, "990099");

    fillSquareArea(fb, x-8, y+4, x+20, y+6, red);
    fillSquareArea(fb, x-8, y+7, x+20, y+9, orange);
    fillSquareArea(fb, x-8, y+10, x+20, y+12, yellow);
    fillSquareArea(fb, x-8, y+13, x+20, y+15, green);
    fillSquareArea(fb, x-8, y+16, x+20, y+18, blue);
    fillSquareArea(fb, x-8, y+19, x+20, y+21, purple);
}

int main(){
    int nyanX, nyanY, topLeftX, topLeftY, botRightX, botRightY;
    int x, y;
    fb = initialize();

    //Initialization
    Color white, black, background;
    Image nyanCat, nyanCat_a;

    initColor(&white, "FFFFFF");
    initColor(&black, "000000");
    initColor(&background, "0c58d3");
    openImage("nyancat", &nyanCat);
    openImage("nyancat_a", &nyanCat_a);
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
        fillSquareArea(&fb, topLeftX, topLeftY,botRightX, botRightY, background);
        drawSquare(&fb, topLeftX, topLeftY,botRightX, botRightY, white);
        drawRainbow(&fb, nyanCat.width+x, y);
        if(x%50>25){
            drawMonoImage(&fb, nyanCat, x, y, white);
        }
        else{
            drawMonoImage(&fb, nyanCat_a, x, y, white);
        }
        
        x--;
        if(x < topLeftX) {
            x = nyanX;               
        }
        if(x%50>25){
            y = nyanY+2;
        }
        else{
            y = nyanY;
        }
        usleep(10000);

        // drawThickLine(&fb, 400, 400, 600, 800, 10, white);
    }

    updateFrame(&fb);
    return 0;
}
