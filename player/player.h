#ifndef PLAYER_H
#define PLAYER_H

#include "util/shp.h"
#include "input/input.h"

void init_player(
        struct uvec     pos
);

void free_player( );

void move_player(
        int             cmd
);

//void do_cmd(
//        struct action   cmd
//);

void draw_player( );

#endif
