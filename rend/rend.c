#include "rend.h"

#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "colour/colour.h"

#define PIPE_CHAR       124
#define PLUS_CHAR       43

static struct {
        struct pixel   *pxs     ;
        struct uvec     dim     ;
} viewbuf;

static void tb_border();


void init_vb(
        struct uvec     _dim
) {
        viewbuf.dim     = _dim;
        int     sz      = viewbuf.dim.x * viewbuf.dim.y;
        viewbuf.pxs     = malloc(sz * sizeof(struct pixel));
        struct pixel blank = {
                .c = 32,
                .col = COL_L_GRAY
        };
        for (int i = 0; i < sz; ++i) {
                viewbuf.pxs[i] = blank;
        }
}

void free_vb( ) {
        free(viewbuf.pxs);
        viewbuf.pxs = NULL;
}

int blit_img(
        struct text     t
) {
        if (!vcont(t.bb.pos)) {
                return ERRF;
        }

        struct pixel   *write = &(viewbuf.pxs[
                                t.bb.pos.y * viewbuf.dim.x + t.bb.pos.x]);
        struct pixel   *read  = t.img;
        struct uvec     curr  = { 0, 0 };

        for (int i = 0; i < t.bb.dim.x * t.bb.dim.y; ++i) {
                if (32 != read->c) {
                        curr.x = t.bb.pos.x + (i % t.bb.dim.x);
                        curr.y = t.bb.pos.y + (i / t.bb.dim.x);
                        if (vcont(curr)) {
                                *write = *read;
                        }
                }

                write++;

                read++;
                if ((i + 1) % t.bb.dim.x == 0) {
                        write += viewbuf.dim.x - t.bb.dim.x;
                }
        }

        return FINE;
}
        
void flush_vb( ) {
        system("clear");

        struct pixel curr;
        int col = COL_FALL;

        tb_border();
        for (int y = 0; y < viewbuf.dim.y; ++y) {
                printf("|");
                for (int x = 0; x < viewbuf.dim.x; ++x) {
                        curr = viewbuf.pxs[y * viewbuf.dim.x + x];
                        if (curr.col != col) {
                                colourise(curr.col);
                                col = curr.col;
                        }
                        printf("%c", curr.c);
                }
                colourise(COL_WHITE);
                col = COL_FALL;
                printf("|\n");
        }
        tb_border();
}

static void tb_border() {
        printf("+");
        for (int x = 0; x < viewbuf.dim.x; ++x) {
                printf("-");
        }
        printf("+\n");
}


int vcont(
        struct uvec     v
) {
        return v.x < viewbuf.dim.x && v.y < viewbuf.dim.y;
}


