#include "world.h"

#include "util/util.h"
#include "util/shp.h"
#include "rend/text.h"

#include <stdio.h>
#include <stdlib.h>

#define STAT_NO 0
#define STAT_RT 0
#define STAT_RW 1
#define STAT_RH 2
#define STAT_RX 3
#define STAT_RY 4
#define STAT_RC 5
#define STAT_EE 6

#define CHAR_W          87
#define CHAR_H          72
#define CHAR_X          88  
#define CHAR_Y          89
#define CHAR_T          84
#define CHAR_C          67
#define CHAR_E          69
#define CHAR_CIRCUM     94

#define WORLD_FILE      "world"
#define MAX_OBJ_C       32
#define MAX_LINE_LEN    64

static struct {
        int             obj_c   ;
        struct text    *texmap  ;
} world;

static void read_data( );

static int add_tex(
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
        read_data();
}

void free_world( ) { }

int blit_world( ) {
        for (int i = 0; i < world.obj_c; ++i) {
                if (ERRF == blit_img(world.texmap[i])) {
                        return ERRF;
                }
        }

        return FINE;
}

static void read_data( ) {
        FILE *f = fopen(WORLD_FILE, "r");
        if (NULL == f) {
                // error
                return;
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
        static int obj_c = 0;           // only initialised once
        static int c_found = FALSE;
        
        struct text t = decode_line(line);

        if (NULL == t.img) {
                world.obj_c = t.bb.pos.x;
                c_found = TRUE;
                return TRUE;
        } else if (FALSE == c_found) {
                return FALSE;
        }

        world.texmap[obj_c++] = t;
        return obj_c < world.obj_c;
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
                        if (STAT_RC == stat) {
                                struct text t = { NULL, bb };
                                return t;
                        }
                }
                
                stat = get_stat(*(++lsc));
                if (STAT_EE == stat) {
                        break;
                }
                beg = ++lsc;
                continue;
        }

        return make_t(beg, bb.dim, bb.pos);     // reads upto ^E !!
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
        case CHAR_C:
                return STAT_RC;
        case CHAR_E:
        default:
                return STAT_EE;
        }
}

static void set_val(
        int             val     ,
        int             stat    ,
        struct rect    *bb
) {
        switch (stat) {
        case STAT_RW:
                bb->dim.x = val;
                break;
        case STAT_RH:
                bb->dim.y = val;
                break;
        case STAT_RX:
                bb->pos.x = val;
                break;
        case STAT_RY:
                bb->pos.y = val;
                break;
        case STAT_RC:
                bb->pos.x = val;
                break;
        default:
                // inaccessible I believe
                break;
        }
}
