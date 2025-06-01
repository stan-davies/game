#include "input.h"
#include "util/util.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_CMD_LEN     8
// lowercase
#define CHAR_H          104
#define CHAR_J          106
#define CHAR_K          107
#define CHAR_L          108
#define CHAR_U          117
// this is of course lowercase too
#define CHAR_LF         10

#define LEFT_BIT        0       // _00
#define RIGHT_BIT       1       // _01
#define DOWN_BIT        2       // _10
#define UP_BIT          3       // _11
#define MOVE_BIT        0       // 0__
#define USE_BIT         4       // 1__

static struct {
        char           *base    ;
        char           *scratch ;
} inbuf;

// ------

static void clean( );

static void readin( );

static int stoa(
        struct action  *act
);

// ------ 

void init_actor( ) {
        inbuf.base = calloc(MAX_CMD_LEN, sizeof(char));
        inbuf.scratch = inbuf.base;
}

void free_actor( ) {
        free(inbuf.base);
        inbuf.base = NULL;
        inbuf.scratch = NULL;
}

struct action getact( ) {
        clean();

        readin();

        struct action act = {
                .act = INVALID_ACTION   ,
                .mod = INVALID_ACTION   ,
        };
        if (ERRF == stoa(&act)) {
                printf("error in stoa\n");
        }
        return act;
}

static void clean( ) {
        inbuf.scratch = inbuf.base;
        for (;;) {
                if (MAX_CMD_LEN == inbuf.scratch - inbuf.base) {
                        break;
                }
                *(inbuf.scratch++) = 0;
        }
        inbuf.scratch = inbuf.base;
}

static void readin( ) {
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
        struct action  *act
) {
        inbuf.scratch = inbuf.base;

        char c;
        for (;;) {
                c = *inbuf.scratch;
                if (c < 48 || c > 57) {
                        break;
                }
                inbuf.scratch++;
        }
        
        int di = inbuf.scratch - inbuf.base;

        if (MAX_CMD_LEN == di) {
                return ERRF;
        } else if (0 == di) {
                act->mod = 1;
        } else {
                char tmp = *inbuf.scratch;
                *inbuf.scratch = 0;
                int m = atoi(inbuf.base);
                if (m <= 0) {
                        return ERRF;
                        // can't be less than 0 as only numerics are collected
                }
                act->mod = m;
                *inbuf.scratch = tmp;
        }

        act->act = 0;
        for (;;) {
                switch (*inbuf.scratch) {
                case CHAR_L:
                        act->act |= RIGHT_BIT;
                        goto end;
                case CHAR_H:
                        act->act |= LEFT_BIT;
                        goto end;
                case CHAR_J:
                        act->act |= DOWN_BIT;
                        goto end;
                case CHAR_K:
                        act->act |= UP_BIT;
                        goto end;
                case CHAR_U:
                        act->act |= USE_BIT;
                        break;
                default:
                        return ERRF;
                }
                inbuf.scratch++;
                if (inbuf.scratch - inbuf.base == MAX_CMD_LEN) {
                        return ERRF;
                }
        }

end:
        return FINE;
}
