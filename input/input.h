#ifndef INPUT_H
#define INPUT_H

#define INVALID_ACTION  -1

// actions
#define MV_LEFT         0       // 000
#define MV_RIGHT        1       // 001
#define MV_DOWN         2       // 010
#define MV_UP           3       // 011
#define US_LEFT         4       // 100
#define US_RIGHT        5       // 101
#define US_DOWN         6       // 110
#define US_UP           7       // 111

#define CMD_QUIT        8


struct action {
        int             act     ;
        int             mod     ;
};

void init_actor( );

void free_actor( );

struct action getact( );

#endif
