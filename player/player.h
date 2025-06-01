#ifndef PLAYER_H
#define PLAYER_H

#include "shp/shp.h"
#include "input/input.h"

void init_player(
        struct uvec     pos
);

void free_player( );

void do_cmd(
        struct action   cmd
);

#endif
