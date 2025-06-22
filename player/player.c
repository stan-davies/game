#include "player.h"

#include "rend/text.h"
#include "rend/rend.h"

#include <stdio.h>

static struct {
        struct uvec     pos     ;
        struct text     t       ;
} player;

void init_player(
        struct uvec     _pos
) {
        player.pos = _pos;

        struct uvec dim = { 1, 1 };
        player.t = make_t("A^E", dim, player.pos);
}

void free_player( ) {
        free_t(&player.t);
}

void move_player(
        int             dir
) {
        int mov = player.pos.y + dir;
        if (!yin_padded(mov)) {
                return;
        }

        player.pos.y = mov;
}

void draw_player( ) {
        // Would not normally update a texture like this but whatever lol.
        player.t.bb.pos.y = player.pos.y;
        blit_img(player.t);
        // Can't error as player is never off screen due to movement checks.       // have not yet implemented said checks but the logic still checks out).
}
