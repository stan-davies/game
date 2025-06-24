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
#define EXPLODE_TEXT    "^;*^E"

#define ENTT_EMPTY      0
#define ENTT_ENEMY      1
#define ENTT_LASER      2

#define NULL_ENT        (struct ent){ ENTT_EMPTY, { { 0 }, NULL } }

struct ent {
        int             typ     ;
        struct text     tex     ;
};

static struct {
        struct ent     *ents    ;
        struct ent     *write   ;
        int             full    ;       // Not really necessary, known to be
                                        // full if the write pointer points to
                                        // a proper entity (not ENT_NULL).
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

static int find_hits(
        struct uvec     la_pos
);

static void dest_ent(
//        int             ent_i
        struct ent     *dent
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

void spawn_laser(
        struct uvec     pos
) {
        if (carrier.full) {
                return;
        }

        pos.x++;

        *carrier.write = (struct ent){ 
                .typ = ENTT_LASER,
                .tex = make_t(LASER_TEXT, ENT_DIM, pos)
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
                .typ = ENTT_ENEMY,
                .tex = make_t(ENEMY_TEXT, ENT_DIM, newpos)
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
                        // If at player -> lose.
                        break;
                case ENTT_LASER:
                        curr->tex.bb.pos.x += 1;
                        if (find_hits(curr->tex.bb.pos)) {
                                dest_ent(carrier.ents + a);
                                continue;
                        }
                        break;
                case ENTT_EMPTY:
                default:
                        continue;
                }

                blit_img(curr->tex);
        }
}

static int find_hits(
        struct uvec     la_pos
) {
        int *typ_find = &carrier.ents->typ;
        int *base = typ_find;

        uint *en_x;

        struct ent *cent;

        for (;;) {
                if ((typ_find - base) / sizeof(struct ent) >= MAX_ENTITIES) {
                        break;
                }

                if (*typ_find != ENTT_ENEMY) {
                        goto cont;
                }

                en_x = typ_find + 2;
                if (*en_x <= la_pos.x && *(en_x + 1) == la_pos.y) {
                        cent = (struct ent *)typ_find;
                        reframe_t(&cent->tex, EXPLODE_TEXT);
                        blit_img(cent->tex);
                        dest_ent(cent);
                        return TRUE;
                }

cont:
                typ_find += sizeof(struct ent) / sizeof(int);
        }

        return FALSE;
}

static void dest_ent(
        struct ent     *dent
) {
        carrier.full = FALSE;

        free_t(&dent->tex);
        *dent = NULL_ENT;

        // Essential only for when previously full, easiest to just always do.
        carrier.write = dent;
}
