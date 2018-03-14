#ifndef NBINPUT_H
#define NBINPUT_H

#include <stdio.h>
#include <sys/time.h>
#include <termios.h>
#include <unistd.h>

#define NB_ENABLE 1
#define NB_DISABLE 0

int kbhit();

void nonblock(int state);

#endif