#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

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
void initTermios(int echo) {
    tcgetattr(0, &old);
    new = old;
    new.c_lflag &= ~ICANON;
    new.c_lflag &= echo ? ECHO : ~ECHO;
    tcsetattr(0, TCSANOW, &new);
}

/* Restore old terminal i/o settings */
void resetTermios(void) {
    tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) {
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

/* Read 1 character without echo */
char getch(void) {
    return getch_(0);
}

int initMouse() {
    int bytes;
    const char *pDevice = "/dev/input/mice";

    // Open Mouse
    int mouse = open(pDevice, O_RDWR);
    if (mouse == -1) {
        printf("ERROR Opening %s\n", pDevice);
        return -1;
    }
}

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

    FrameBuffer fb = initFrameBuffer();
    char command;
    printf("== Menu ==\n");
    printf("1. Task 1 - Bitmap Font\n");
    printf("2. Task 2 - Nyan Cat\n");
    printf("3. Task 3 - Vector Font\n");
    printf("4. Task 4 - Airplane\n");
    printf("5. Task 5 - Clipping\n");
    printf("6. Task 6 - ITB 2D\n");
    printf("7. Task 7 - Mouse\n");
    printf("\nCommand: ");
    scanf("%c", &command);

    while (command != 'q') {
        if (command == '1') {
            system("clear");
            Font f;
            Color c;

            openFont("archaic", &f);
            c.r = 255;
            c.g = 255;
            c.b = 255;
            c.a = 0;

            char in[1000];
            printf("Input: ");
            scanf("%s", in);
            getchar();
            printString(&fb, in, f, 200, 200, c);
        } else if (command == '2') {
            system("clear");
            int nyanX, nyanY, topLeftX, topLeftY, botRightX, botRightY;
            int x, y;

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
                drawSquare(&fb, topLeftX, topLeftY, botRightX, botRightY,
                           white);
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
                drawThickLine(&fb, line1x0, line1y0, line1x1, line1y1, 2,
                              orange);

                laser2 = (line1x1 <= lineInitX - 30) ? 1 : 0;
                if (laser2) {
                    line2y0 -= 5;
                    line2y1 -= 5;
                    drawThickLine(&fb, line2x0, line2y0, line2x1, line2y1, 3,
                                  yellow);
                }

                laser3 = (line2y1 <= lineInitY - 40) ? 1 : 0;
                if (laser3) {
                    line3x0 += 5;
                    line3y0 -= 5;
                    line3x1 += 5;
                    line3y1 -= 5;
                    drawThickLine(&fb, line3x0, line3y0, line3x1, line3y1, 4,
                                  green);
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
        } else if (command == '3') {
            system("clear");
            // Color initialization
            Color white, black, grey, pink, background;
            Color orange, yellow, green;

            initColor(&orange, "FF7800");
            initColor(&yellow, "FFFF00");
            initColor(&green, "00FF00");
            initColor(&white, "FFFFFF");
            initColor(&black, "000000");
            initColor(&grey, "77797A");
            initColor(&pink, "FF8AD1");
            initColor(&background, "0D1B46");

            // Raster font initialization
            RasterFont rasterFont;
            initRasterFont(&rasterFont);
            openRasterFont("raster_font", &rasterFont);

            // Clear screen
            //printf("\e[1;1H\e[2J");

            // Draw and fill
            Vertex v;
            v.x = 300;
            v.y = 100;

            // for (int i = (int)'a'; i <= (int)'z'; i++) {
            //     fillChar(&fb, (char)i, &rasterFont, v, yellow);
            //     v.x += 100;
            //     if (v.x > 1000) {
            //         v.y += 130;
            //         v.x = 300;
            //     }
            // }

            char input[1000];

            printf("Input string: ");
            // scanf("%999[0-9a-zA-Z ]", input);
            scanf("%s", input);
            getchar();

            // Convert to lowercase
            for (int i = 0; input[i]; i++) {
                input[i] = tolower((char)input[i]);
            }

            fillString(&fb, input, &rasterFont, v, pink);
        } else if (command == '4') {
            system("clear");
            VectorImage plane;
            VectorImage blade_left;
            VectorImage blade_right;

            int screen_width = fb.vinfo.xres;
            int screen_height = fb.vinfo.yres;

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
            startingVertex.x = 0;
            startingVertex.y = 0;
            endingVertex.x = screen_width;
            endingVertex.y = screen_height;
            initSquareClipper(&clipper, startingVertex.x, startingVertex.y,
                              endingVertex.x, endingVertex.y);

            Color yellow;
            initColor(&yellow, "FFF000");

            printf("hehehe\n");
            while (1) {
                // printf("HEHEHE\n");
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

                clearArea(&fb, startingVertex, endingVertex);
                //system("clear");

                clipVectorImage(&plane2, clipper);
                clipVectorImage(&blade_left2, clipper);
                clipVectorImage(&blade_right2, clipper);

                drawSquare(&fb, startingVertex.x, startingVertex.y,
                           endingVertex.x, endingVertex.y, yellow);
                fillImage(&fb, &plane2, v);
                fillImage(&fb, &blade_left2, v);
                fillImage(&fb, &blade_right2, v);

                end = clock();

                // sleep(50);
                // 66000 for 30fps
                renderTime =
                    33000 -
                    (((double)(end - start)) / CLOCKS_PER_SEC) * 1000000;

                if (renderTime > 0) {

                    usleep(renderTime);
                }

                deg += 30;
                scale += 0.1;
            }
        } else if (command == '5') {
            system("clear");
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
            startingVertex.x = 0;
            startingVertex.y = 0;
            endingVertex.x = 600;
            endingVertex.y = 600;
            initSquareClipper(&clipper, startingVertex.x, startingVertex.y,
                              endingVertex.x, endingVertex.y);

            Color yellow;
            initColor(&yellow, "FFF000");

            printf("hehehe\n");
            while (1) {
                // printf("HEHEHE\n");
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

                clearArea(&fb, startingVertex, endingVertex);
                //system("clear");

                clipVectorImage(&plane2, clipper);
                clipVectorImage(&blade_left2, clipper);
                clipVectorImage(&blade_right2, clipper);

                drawSquare(&fb, startingVertex.x, startingVertex.y,
                           endingVertex.x, endingVertex.y, yellow);
                fillImage(&fb, &plane2, v);
                fillImage(&fb, &blade_left2, v);
                fillImage(&fb, &blade_right2, v);

                end = clock();

                // sleep(50);
                // 66000 for 30fps
                renderTime =
                    33000 -
                    (((double)(end - start)) / CLOCKS_PER_SEC) * 1000000;

                if (renderTime > 0) {

                    usleep(renderTime);
                }

                deg += 30;
                scale += 0.1;
            }
        } else if (command == '6') {
            system("clear");
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
                drawSquare(&fb, startingVertex.x, startingVertex.y,
                           endingVertex.x, endingVertex.y, yellow);

                clipVectorImage(&itb_gedung2, clipper);
                clipVectorImage(&itb_jalan2, clipper);

                fillImage(&fb, &itb_gedung2, v);
                fillImage(&fb, &itb_jalan2, v);

                if (getch() == '\033') {
                    getch();
                    switch (getch()) {
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
        } else if (command == '7') {
            system("clear");
            time_t start, end;
            long renderTime;

            int bytes;
            int mouse = initMouse();
            unsigned char mouseState[3];

            VectorImage cursor;
            openVectorImage("cursor", &cursor);

            int8_t x = 0;
            int8_t y = 0;
            Vertex position;
            Vertex distance;
            Vertex clearLocationSt, clearLocationEn;
            position.x = 854;
            position.y = 384;

            distance.x = 0;
            distance.y = 0;

            while (1) {
                bytes = read(mouse, mouseState, sizeof(mouseState));
                if (bytes > 0) {
                    start = clock();
                    // left = data[0] & 0x1;
                    // right = data[0] & 0x2;
                    // middle = data[0] & 0x4;
                    // x = data[1];
                    // y = data[2];
                    x = mouseState[1];
                    y = mouseState[2];
                    distance.x = x;
                    distance.y = -y;

                    translateVectorImage(&cursor, distance);
                    fillImage(&fb, &cursor, position);

                    end = clock();

                    // 66000 for 30fps
                    renderTime =
                        33000 -
                        (((double)(end - start)) / CLOCKS_PER_SEC) * 1000000;
                    if (renderTime > 0) {
                        usleep(renderTime);
                    }

                    calculateVectorImageBoundaries(&cursor);
                    clearLocationSt.x = cursor.upperLeft.x + position.x;
                    clearLocationSt.y = cursor.upperLeft.y + position.y;

                    clearLocationEn.x = cursor.lowerRight.x + position.x;
                    clearLocationEn.y = cursor.lowerRight.y + position.y;
                    clearArea(&fb, clearLocationSt, clearLocationEn);
                }
            }
        } else {
            printf("Invalid command\n");
        }
        printf("\n\n== Menu ==\n");
        printf("1. Task 1 - Bitmap Font\n");
        printf("2. Task 2 - Nyan Cat\n");
        printf("3. Task 3 - Vector Font\n");
        printf("4. Task 4 - Airplane\n");
        printf("5. Task 5 - Clipping\n");
        printf("6. Task 6 - ITB 2D\n");
        printf("7. Task 7 - Mouse\n");
        printf("\nCommand: ");
        scanf("%c", &command);
    }

    printf("End of program\n");

    return 0;
}
