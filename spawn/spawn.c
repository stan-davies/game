#include "spawn.h"

#include "util/util.h"
#include "rend/rend.h"
#include "rend/text.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SPAWN_RATE      45      // Percentage chance of a spawn each cycle.
#define MAX_ENEMIES     12

#define ENEMY_TEXT      "^1#^E"

#define NULL_TEXT       (struct text){ NULL, { -1 } }

static struct {
        struct text    *enemies ;
        struct text    *write_e ;
        struct uvec     spawnat ;
        int             full    ;
} cage;

static void do_spawn(
        void
);

static void update_en(
        void
);

void init_spawn(
        void
) {
        srand(time(NULL));

        cage.enemies = calloc(MAX_ENEMIES, sizeof(struct uvec));
        cage.write_e = cage.enemies;

        cage.spawnat = give_dim();
        cage.spawnat.y /= 4;

        cage.full    = FALSE;
}

void free_spawn(
        void
) {
        free(cage.enemies);
        cage.enemies = NULL;
        cage.write_e = NULL;
}

void poll_spawn(
        void
) {
        do_spawn();
        update_en();
}

void kill_en(
        int             y
) {
        cage.full &= FALSE;

        struct uvec p;
        int lowx = 100;
        int lowa = -1;

        for (int a = 0; a < MAX_ENEMIES; ++a) {
                p = cage.enemies[a].bb.pos;
                if (p.y == y && p.x < lowx) {
                        lowx = p.x;
                        lowa = a;
                }
        }

        if (-1 == lowa) {
                return;
        }

        free_t(&cage.enemies[lowa]);
        cage.enemies[lowa] = NULL_TEXT;
}

static void do_spawn(
        void
) {
        int seed = rand() % 100;

        if (cage.full || seed % 100 > SPAWN_RATE) {
                return;
        }

        struct uvec newpos = {
                .x = cage.spawnat.x,
                .y = (seed % (2 * cage.spawnat.y)) + cage.spawnat.y
        };
        struct uvec dim = { 1, 1 };

        // Different texture thing?
//        char *tex = calloc(6, sizeof(char));
//        sprintf(tex, "^1%ld^E", cage.write_e - cage.enemies);

        *cage.write_e = make_t(ENEMY_TEXT, dim, newpos);

//        free(tex);
//        tex = NULL;

        struct text *pre = cage.write_e;
        for (;;) {
                if ((++cage.write_e) - cage.enemies >= MAX_ENEMIES) {
                        cage.write_e = cage.enemies;
                }
                if (cage.write_e->bb.pos.x == -1) {
                        break;
                } else if (cage.write_e == pre) {
                        cage.full = TRUE;
                        break;
                }
        }
}

static void update_en(
        void
) {
        for (int a = 0; a < MAX_ENEMIES; ++a) {
                if (cage.enemies[a].bb.pos.x == -1) {
                        continue;
                }
                cage.enemies[a].bb.pos.x -= 1;

                blit_img(cage.enemies[a]);
        }
}
