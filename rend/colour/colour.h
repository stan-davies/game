#ifndef COLOUR_H
#define COLOUR_H

#define COL_FALL       -1       // do nothing  -  in both senses
#define COL_BLACK       0       // ^0
#define COL_RED         1       // ^1
#define COL_GREEN       2       // ^2
#define COL_ORANGE      3       // ^3
#define COL_BLUE        4       // ^4
#define COL_PURPLE      5       // ^5
#define COL_CYAN        6       // ^6
#define COL_L_GRAY      7       // ^7
#define COL_D_GRAY      8       // ^8
#define COL_L_RED       9       // ^9
#define COL_L_GREEN     10      // ^:
#define COL_YELLOW      11      // ^;
#define COL_L_BLUE      12      // ^<
#define COL_L_PURPLE    13      // ^=
#define COL_L_CYAN      14      // ^>
#define COL_WHITE       15      // ^?  -  no colour

void colourise(
        int             col
);

#endif
