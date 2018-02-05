#include "font.h"

void openFont(char *fontChar, Font *font) {
    for (int i = 0; i < 256; i++) {
        (*font).dict[i] = (char *)malloc(100);
    }

    int c = 'a';
    char fontFilename[30];
    strcpy(fontFilename, "fonts/");
    strcat(fontFilename, fontChar);
    strcat(fontFilename, ".txt");

    FILE *fontFile;
    fontFile = fopen(fontFilename, "r");
    if (fontFile) {
        fscanf(fontFile, "%d", &((*font).width));
        fscanf(fontFile, "%d", &((*font).height));
        while ((fscanf(fontFile, "%s", (*font).dict[c]) == 1) && (c <= 'z')) {
            c++;
        }

        if (c == 'z' + 1) {
            printf("Successfully loaded font %s\n", fontChar);
        } else {
            printf("Error in reading font %s\n", fontChar);
        }
        fclose(fontFile);
    } else {
        printf("Font does not exist\n");
        exit(5);
    }
}
