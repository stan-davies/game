#include "input.h"
#include "util/util.h"
#include "player/player.h"

#include <stdio.h>              // Used for more than just `printf`!
#include <stdlib.h>

#define MAX_CMD_LEN     8
// lowercase
#define CHAR_D          100
#define CHAR_J          106
#define CHAR_Q          113
// this is of course lowercase too
#define CHAR_LF         10

static struct {
        char           *base    ;
        char           *scratch ;
} inbuf;

// ------

static void clean(
        void
);

static void readin(
        void
);

//static void stoa(
//        struct action  *act
//);

static int stoa(
        void
);

// ------ 

void init_actor(
        void
) {
        inbuf.base = calloc(MAX_CMD_LEN, sizeof(char));
        inbuf.scratch = inbuf.base;
}

void free_actor(
        void
) {
        free(inbuf.base);
        inbuf.base = NULL;
        inbuf.scratch = NULL;
}

int getact(
        void
) {
        clean();
        readin();
        return stoa();
}

static void clean(
        void
) {
        inbuf.scratch = inbuf.base;
        for (;;) {
                if (MAX_CMD_LEN == inbuf.scratch - inbuf.base) {
                        break;
                }
                *(inbuf.scratch++) = 0;
        }
        inbuf.scratch = inbuf.base;
}

static void readin(
        void
) {
        int in;
        for (;;) {
                in = getchar();
                if (EOF == in 
                        || MAX_CMD_LEN == (inbuf.scratch - inbuf.base)
                        || CHAR_LF == in
                ) {
                        break;
                }
                *(inbuf.scratch++) = in;                
        }
}

static int stoa(
        void
) {
        switch (inbuf.base[0]) {
        case CHAR_J:
                move_player(1);
                break;
        case CHAR_D:
                move_player(-1);
                break;
        case CHAR_Q:
                return FALSE;
        default:
                break;
        }

        return TRUE;
}
