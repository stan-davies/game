#ifndef PLAYER_H
#define PLAYER_H

#include "util/shp.h"
#include "input/input.h"

void init_player(
        struct uvec     pos
);

void free_player(
        void
);

struct uvec give_pp(
        void
);

void move_player(
        int             cmd
);

void player_shoot(
        void
);

void draw_player(
        void
);

#endif
