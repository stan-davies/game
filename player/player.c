#include "player.h"

static struct {
//        struct room     curr    ;
        struct uvec     pos     ;
        uint            hlth    ;
        // inventory?
        // what else?
} player;

void init_player(
        struct uvec     _pos
) {
        player.pos = _pos;
        player.hlth = 0;
}

int move(
        struct uvec     dir
) {
        struct uvec new = {
                player.pos.x + dir.x    ,
                player.pos.y + dir.y
        };

        if (FALSE == vcont) {
                return ERRF;
        }

        player.pos = new;
}

