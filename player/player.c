#include "player.h"

#include "rend/text.h"
#include "rend/rend.h"

#include <stdio.h>

static struct {
        struct uvec     pos     ;
        struct text     t       ;
        // inventory, other data, blah blah blah
} player;

void init_player(
        struct uvec     _pos
) {
        player.pos = _pos;

        struct uvec dim = { 1, 1 };
        player.t = make_t("A", dim, player.pos);
}

void free_player( ) {
        free_t(&player.t);
}

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

void draw_player( ) {
        // Would not normally update a texture like this but whatever lol.
        player.t.bb.pos = player.pos;
        blit_img(player.t);
        // Can't error as player is never off screen due to movement checks. (I
        // have not yet implemented said checks but the logic still checks out).
}
