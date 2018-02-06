#include <string.h>

#include "rasterizer.h"

void boundaryFill(FrameBuffer *fb, int x, int y, Color c) {
    // Check screen boundaries
    if ((x < 0) || (x >= fb->screen_width) || (y < 0) ||
        (y >= fb->screen_height))
        return;

    // Output to screen
    Color curr = getColor(fb, x, y);
    if (!isSameColor(curr, c)) {
        addPixelToBuffer(fb, x, y, c.r, c.g, c.b, c.a);
        boundaryFill(fb, x, y - 1, c);
        boundaryFill(fb, x, y + 1, c);
        boundaryFill(fb, x - 1, y, c);
        boundaryFill(fb, x + 1, y, c);
    }
}


int inCriticalList(int x, int y, Vertex* v, int vCount){
    int retVal = 0;
    int i=0;
    while(i<vCount && retVal == 0){
        if(v[i].x == x && v[i].y == y){
            retVal = 1;
        }
        else {
            i++;
        }
    }

    return retVal;
}

void scanlineFill(FrameBuffer *fb, Shape *s, Color c) {

    Color white;
    Vertex v[999];
    int vCount = 0;
    float grad0, grad1;
    initColor(&white, "FFFFFF");
    int j;

    int minX = findMinXInShape(s->polygons, s->polygonCount);
    int maxX = findMaxXInShape(s->polygons, s->polygonCount);
    int minY = findMinYInShape(s->polygons, s->polygonCount);
    int maxY = findMaxYInShape(s->polygons, s->polygonCount);

    for (int i = 0; i < s->polygonCount; ++i) {
        drawPolygon(fb, &(s->polygons[i]), white);

        //Find critical vertex
        grad0 = countGrad((*s).polygons[i].vertices[0],(*s).polygons[i].vertices[(*s).polygons[i].vertexCount-1]);
        grad1 = countGrad((*s).polygons[i].vertices[0],(*s).polygons[i].vertices[1]);
        if((grad0 < 0 && grad1 > 0) || (grad0 > 0 && grad1 < 0)){
                v[vCount] = (*s).polygons[i].vertices[j];
                vCount++;
        }

        for(j = 1; j < (*s).polygons[i].vertexCount-1; j++){
            grad0 = countGrad((*s).polygons[i].vertices[j],(*s).polygons[i].vertices[j-1]);
            grad1 = countGrad((*s).polygons[i].vertices[j],(*s).polygons[i].vertices[j+1]);
            if((grad0 < 0 && grad1 > 0) || (grad0 > 0 && grad1 < 0)){
                v[vCount] = (*s).polygons[i].vertices[j];
                vCount++;
            }
        }

        grad0 = countGrad((*s).polygons[i].vertices[j],(*s).polygons[i].vertices[j-1]);
        grad1 = countGrad((*s).polygons[i].vertices[j],(*s).polygons[i].vertices[0]);
        if((grad0 < 0 && grad1 > 0) || (grad0 > 0 && grad1 < 0)){
                v[vCount] = (*s).polygons[i].vertices[j];
                vCount++;
        }
    }    

    // Color Fill
    int colorize = 0;
    for (int y = minY; y <= maxY; y++) {
        Color curr = getColor(fb, minX, y);
        colorize = 0;

        for (int x = minX; x <= maxX; x++) {
            curr = getColor(fb, x, y);
            if (isSameColor(curr, white)) {
                if(!inCriticalList(x, y, &v, vCount)){
                    colorize = !colorize;

                    continue;
                }
            }

            if (colorize) {
                addPixelToBuffer(fb, x, y, c.r, c.g, c.b, c.a);
            }
        }
    }
}

void fillShape(FrameBuffer *fb, Shape *s, Color c) {
    for (int i = 0; i < s->polygonCount; ++i) {
        drawPolygon(fb, &(s->polygons[i]), c);
    }

    // Get point in polygon
    // TODO: make a better one
    Vertex v = s->polygons[0].vertices[0];
    v.x++;
    v.y++;

    // Boundary fill
    // boundaryFill(fb, v.x, v.y, c);

    // Scanline fill
    scanlineFill(fb, s, c);

    updateFrame(fb);
}

void fillChar(FrameBuffer *fb, char ch, RasterFont *rasterFont, Vertex offset,
              Color c) {
    offsetShape(&(rasterFont->dict[(int)ch]), offset);
    fillShape(fb, &(rasterFont->dict[(int)ch]), c);
}

void fillString(FrameBuffer *fb, char *s, RasterFont *rasterFont, Vertex offset,
                Color c) {
    Vertex origin = offset;
    int len = strlen(s);

    int i;
    for (i = 0; i < len; ++i) {
        fillChar(fb, s[i], rasterFont, offset, c);

        // Manage offset
        if (offset.x + 2 * rasterFont->width >= fb->screen_width) {
            offset.x = origin.x;
            offset.y += rasterFont->height;

            if (offset.y >= fb->screen_height)
                return;
        } else {
            offset.x += rasterFont->width;
        }
    }
}

void fillSquareArea(FrameBuffer *fb, int x0, int y0, int x1, int y1, Color c) {
    for (int x = x0; x <= x1; x++) {
        for (int y = y0; y <= y1; y++) {
            addPixelToBuffer(fb, x, y, c.r, c.g, c.b, c.a);
        }
    }
}

void fillRainbow(FrameBuffer *fb, int x, int y) {
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
