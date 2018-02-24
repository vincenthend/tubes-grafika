#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "color.h"
#include "drawer.h"
#include "framebuffer.h"
#include "graphics.h"
#include "printer.h"

FrameBuffer fb;
void drawRainbow(FrameBuffer *fb, int x, int y) {
    Color red, orange, yellow, green, blue, purple;
    initColor(&red, "FF0000");
    initColor(&orange, "FF7700");
    initColor(&yellow, "FFFF00");
    initColor(&green, "009900");
    initColor(&blue, "000099");
    initColor(&purple, "990099");

    fillSquareArea(fb, x - 8, y + 4, x + 20, y + 6, red);
    fillSquareArea(fb, x - 8, y + 7, x + 20, y + 9, orange);
    fillSquareArea(fb, x - 8, y + 10, x + 20, y + 12, yellow);
    fillSquareArea(fb, x - 8, y + 13, x + 20, y + 15, green);
    fillSquareArea(fb, x - 8, y + 16, x + 20, y + 18, blue);
    fillSquareArea(fb, x - 8, y + 19, x + 20, y + 21, purple);
}

int main() {
    int nyanX, nyanY, topLeftX, topLeftY, botRightX, botRightY;
    int x, y;
    fb = initialize();

    //Initialization
    Color white, black, grey, pink, background;
    Color orange, yellow, green;
    Image nyanCat, nyanCat_a;

    initColor(&orange, "ff7800");
    initColor(&yellow, "FFFF00");
    initColor(&green, "00ff00");
    initColor(&white, "FFFFFF");
    initColor(&black, "000000");
    initColor(&grey, "77797A");
    initColor(&pink, "FF8AD1");
    initColor(&background, "0d1b46");

    openImage("nyancat", &nyanCat);
    openImage("nyancat_a", &nyanCat_a);
    topLeftX = fb.screen_width - 900;
    topLeftY = fb.screen_height - 800;
    botRightX = fb.screen_width - 100;
    botRightY = fb.screen_height - 400;
    nyanX = botRightX - 60;
    nyanY = botRightY - 350;
    x = nyanX;
    y = nyanY;

    //Line matter
    int lineInitX = botRightX - 410;
    int lineInitY = botRightY - 50;

    int line1x0 = lineInitX, line1y0 = lineInitY;
    int line1x1 = lineInitX - 10;
    int line1y1 = lineInitY - 10;

    int line2x0 = lineInitX, line2y0 = lineInitY;
    int line2x1 = lineInitX, line2y1 = lineInitY - 10;

    int line3x0 = lineInitX, line3y0 = lineInitY;
    int line3x1 = lineInitX + 10, line3y1 = lineInitY - 10;

    int laser2 = 0;
    int laser3 = 0;
    //Loop
    while (1) {
        fillSquareArea(&fb, topLeftX, topLeftY, botRightX, botRightY,
                       background);
        drawSquare(&fb, topLeftX, topLeftY, botRightX, botRightY, white);
        drawRainbow(&fb, nyanCat.width + x, y);
        if (x % 50 > 25) {
            drawNyanImage(&fb, nyanCat, x, y, black, pink, grey);
        } else {
            drawNyanImage(&fb, nyanCat_a, x, y, black, pink, grey);
        }

        x--;
        if (x < topLeftX) {
            x = nyanX;
        }
        if (x % 50 > 25) {
            y = nyanY + 2;
        } else {
            y = nyanY;
        }
        usleep(1000);

        //Line matter
        line1x0 -= 5;
        line1y0 -= 5;
        line1x1 -= 5;
        line1y1 -= 5;
        drawThickLine(&fb, line1x0, line1y0, line1x1, line1y1, 2, orange);

        laser2 = (line1x1 <= lineInitX - 30) ? 1 : 0;
        if (laser2) {
            line2y0 -= 5;
            line2y1 -= 5;
            drawThickLine(&fb, line2x0, line2y0, line2x1, line2y1, 3, yellow);
        }

        laser3 = (line2y1 <= lineInitY - 40) ? 1 : 0;
        if (laser3) {
            line3x0 += 5;
            line3y0 -= 5;
            line3x1 += 5;
            line3y1 -= 5;
            drawThickLine(&fb, line3x0, line3y0, line3x1, line3y1, 4, green);
        }

        if (line1x1 <= topLeftX || line1y1 <= topLeftY + 6) {
            line1x0 = lineInitX;
            line1y0 = lineInitY;
            line1x1 = lineInitX - 10;
            line1y1 = lineInitY - 10;
        }
        if (line2y1 <= topLeftY + 6) {
            line2y0 = lineInitY;
            line2y1 = lineInitY - 10;
        }
        if (line3x0 >= botRightX || line3y1 <= topLeftY + 6) {
            line3x0 = lineInitX;
            line3x1 = lineInitX + 10;
            line3y0 = lineInitY;
            line3y1 = lineInitY - 10;
        }
    }

    updateFrame(&fb);
    return 0;
}
