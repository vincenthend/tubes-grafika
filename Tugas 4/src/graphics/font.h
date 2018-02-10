#ifndef _FONT_H
#define _FONT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * File Font
 * digunakan untuk memanipulasi font bit map
 */

typedef struct {
    char *dict[256];
    int height;
    int width;
} Font;

void openFont(char *ch, Font *font);

#endif
