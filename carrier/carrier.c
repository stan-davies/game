#include "carrier.h"

#include "util/util.h"
#include "rend/rend.h"
#include "rend/text.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EN_SPAWN_RATE   45      // Percentage chance of enemy spawn each cycle.
#define MAX_ENTITIES    32

#define ENT_DIM         (struct uvec){ 1, 1 }
#define ENEMY_TEXT      "^1#^E"
#define LASER_TEXT      "^>-^E"

#define ENTT_EMPTY      0
#define ENTT_ENEMY      1
#define ENTT_LASER      2

#define NULL_ENT        (struct ent){ { NULL, { 0 } }, ENTT_EMPTY }

struct ent {
        struct text     tex     ;
        int             typ     ;
};

static struct {
        struct ent     *ents    ;
        struct ent     *write   ;
        int             full    ;
} carrier;

struct sub {
        struct uvec     spawn   ;
        int             mod     ;
};

static struct sub en_sub;
static struct sub la_sub;               // Useless?

static void spawn_enemy(
        void
);

static void find_emp(
        void
);

static void update_ents(
        void
);

void init_carrier(
        void
) {
        srand(time(NULL));

        carrier.ents    = calloc(MAX_ENTITIES, sizeof(struct ent));
        carrier.write   = carrier.ents;

        carrier.full    = FALSE;

        en_sub.spawn    = give_dim();
        en_sub.spawn.y /= 4;
        en_sub.mod      = EN_SPAWN_RATE;

        la_sub.spawn    = give_pp();
        la_sub.spawn.x += 1;
        la_sub.mod      = -1;
}

void free_carrier(
        void
) {
        free(carrier.ents);
        carrier.ents = NULL;
        carrier.write = NULL;
}

void poll_carrier(
        void
) {
        spawn_enemy();
        update_ents();
}

void kill_ent(
        int             y
) {
        carrier.full = FALSE;

        struct uvec p;
        int lowx = 100;
        int lowa = -1;

        for (int a = 0; a < MAX_ENTITIES; ++a) {
                p = carrier.ents[a].tex.bb.pos;
                if (p.y == y && p.x < lowx) {
                        lowx = p.x;
                        lowa = a;
                }
        }

        if (-1 == lowa) {
                return;
        }

        free_t(&carrier.ents[lowa].tex);
        carrier.ents[lowa] = NULL_ENT;
}

void spawn_laser(
        struct uvec     pos
) {
        if (carrier.full) {
                return;
        }

        pos.x++;

        *carrier.write = (struct ent){ 
                make_t(LASER_TEXT, ENT_DIM, pos),
                ENTT_LASER
        };

        find_emp();
}

static void spawn_enemy(
        void
) {
        int seed = rand() % 100;

        if (carrier.full || seed % 100 > en_sub.mod) {
                return;
        }

        struct uvec newpos = {
                .x = en_sub.spawn.x,
                .y = (seed % (2 * en_sub.spawn.y)) + en_sub.spawn.y
        };

        *carrier.write = (struct ent){ 
                make_t(ENEMY_TEXT, ENT_DIM, newpos),
                ENTT_ENEMY
        };

        find_emp();
}

static void find_emp(
        void
) {
        struct ent *pre = carrier.write;
        for (;;) {
                if ((++carrier.write) - carrier.ents >= MAX_ENTITIES) {
                        carrier.write = carrier.ents;
                }
                if (carrier.write->typ == ENTT_EMPTY) {
                        break;
                } else if (carrier.write == pre) {
                        carrier.full = TRUE;
                        break;
                }
        }
}

static void update_ents(
        void
) {
        struct ent *curr;
        
        for (int a = 0; a < MAX_ENTITIES; ++a) {
                curr = carrier.ents + a;

                switch (curr->typ) {
                case ENTT_ENEMY:
                        curr->tex.bb.pos.x -= 1;
                        break;
                case ENTT_LASER:
                        curr->tex.bb.pos.x += 1;
                        break;
                case ENTT_EMPTY:
                default:
                        continue;
                }

                blit_img(curr->tex);
        }
}
