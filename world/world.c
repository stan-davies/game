#include "world.h"

#include <stdio.h>

#define STAT_NO 0
#define STAT_RT 0
#define STAT_RW 1
#define STAT_RH 2
#define STAT_RX 3
#define STAT_RY 4
#define STAT_EE 6

static struct {
        int             obj_c   ;
        struct text    *texmap  ;
} world;

static void read_data( );

static void add_tex(
        char           *line
);

static struct text decode_line(
        char           *line
);

static int get_stat(
        char            ident
);

static void set_val(
        int             val     ,
        int             stat    ,
        struct rect    *bb
);

void init_world( ) {
        world.obj_c = 0;
        world.texmap = calloc(MAX_OBJ_C, sizeof(struct text));

        // read file
        // establish structure
        // read world data from file
}

void free_world( ) {
}

static void read_data( ) {
        FILE *f = fopen(WORLD_FILE, "r");
        if (NULL == f) {
                // error
        }

        char *line = calloc(MAX_LINE_LEN, sizeof(char));
        struct text t;
        for (;;) {
                if (NULL == fgets(line, MAX_LINE_LEN, f)) {
                        break;
                }

                if (FALSE == add_tex(line)) {
                        break;
                }
        }

        fclose(f);
}

static int add_tex(
        char           *line
) {
        struct text t = decode_line(line);

        world.texmap[world.obj_c++] = t;
        if (world.obj_c >= MAX_OBJ_C) {
                return FALSE;
        }
}

static struct text decode_line(
        char           *line
) {
        struct rect bb = { 0, 0, 0, 0 };
        char *lsc = line;
        char *beg;
        int   stat = STAT_NO;
        int   val;
        char  r;

        for (;;) {
                if (CHAR_CIRCUM != (r = *(lsc++))) {
                        continue;
                }

                if (stat > STAT_NO) {
                        *lsc = 0;
                        set_val(atoi(beg), stat, &bb);
                }
                
                stat = get_stat(*(++lsc));
                if (STAT_EE == stat) {
                        break;
                }
                beg = ++lsc;
                continue;
        }

        return make_t(bb.dim, bb.pos, beg);     // reads upto ^E !!
}

static int get_stat(
        char            ident
) {
        switch (ident) {
        case CHAR_W:
                return STAT_RW;
        case CHAR_H:
                return STAT_RH;
        case CHAR_X:
                return STAT_RX;
        case CHAR_Y:
                return STAT_RY;
        case CHAR_T:
                return STAT_RT;
        case CHAR_E:
                return STAT_EE;
        default:
                return /* aaaaa!!! */
        }
}

static void set_val(
        int             val     ,
        int             stat    ,
        struct rect    *bb
) {
        switch (ident) {
        case CHAR_W:
                bb->dim.x = val;
                break;
        case CHAR_H:
                bb->dim.y = val;
                break;
        case CHAR_X:
                bb->pos.x = val;
                break;
        case CHAR_Y:
                bb->pos.y = val;
                break;
        default:
                break;
        }
}
