#include "util.h"

#define PLAYER_DEFAULT_X        10
#define PLAYER_DEFAULT_Y        10

#define DEFAULT_SCREEN_W        80
#define DEFAULT_SCREEN_H        20

void prog_init( ) {
        init_actor();

        struct uvec ppos = { PLAYER_DEFAULT_X, PLAYER_DEFAULT_Y };
        init_player(ppos);

        struct uvec dim = { DEFAULT_SCREEN_W, DEFAULT_SCREEN_H };
        init_vb(dim);
}

void prog_free( ) {
        free_vb();
        free_player();
        free_actor();
}
