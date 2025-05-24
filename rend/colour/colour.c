#include "colour.h"

#include <stdio.h>

#ifdef SYS_WINDOWS

#include <windows.h>

void colourise(
        int             col
) {
        HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
        
        int colour = 0;
        if (col >= COL_D_GRAY) {
                colour |= FOREGROUND_INTENSITY;
        }

        if (col % 2 == 1) {
                colour |= FOREGROUND_RED;
        }

        if (col % 4 > 1) {
                colour |= FOREGROUND_GREEN;
        }

        if (col % 8 > 3) {
                colour |= FOREGROUND_BLUE;
        }

        SetConsoleTextAttribute(h_console, colour);
}

#else

void colourise(
        int             col
) {
        if (COL_WHITE == col) {
                printf("\033[0m");
                return;
        }

        printf("\033[%d;3%dm", col / 8, col % 8);
}

#endif
