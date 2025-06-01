#include "player.h"

#include <stdio.h>

static struct {
        struct uvec     pos     ;
        char            rep     ;
        // inventory, other data, blah blah blah
} player;

void init_player(
        struct uvec     _pos
) {
        player.pos = _pos;
        player.rep = 65;
}

void free_player( ) { }

void do_cmd(
        struct action   cmd
) {
        struct uvec target;
        target.x = (cmd.act & 3) < 2;           // & => _xx
        target.y = !target.x;

        printf("from : (%d, %d)\n", player.pos.x, player.pos.y);

        if (!(cmd.act >> 2)) {                  // use bit == 0
                int mod = cmd.act % 2 ? cmd.mod : -cmd.mod;
                player.pos.x += target.x * mod;
                player.pos.y += target.y * mod;
                printf("to   : (%d, %d)\n", player.pos.x, player.pos.y);
                // some kind of "if you go outside these boundaries, parallax"
                return;
        }

        // something about
                // 1. get information of target destination
                // 2. 'use' that tile mod times

//        target.x += player.pos.x;
//        target.y += player.pos.y;
//        struct obj object = object_lookup(target);
//
//        for (int u = 0; u < act.mod; ++u) {
//                use(object);
//        }
}
