#include "rend.h"

#include <stdio.h>
#include <stdlib.h>

#include "util.h"

static struct {
        struct pixel   *pxs     ;
        struct uvec     dim     ;
} viewbuf;

void init_vb(
        struct uvec     _dim
) {
        viewbuf.dim     = _dim;
        int     sz      = viewbuf.dim.x * viewbuf.dim.y;
        viewbuf.pxs     = calloc(sz, sizeof(struct pixel));
        for (int i = 0; i < sz; ++i) {
                viewbuf.pxs[i].c = 32;
        }
}

int blit(
        struct rect     rct
) {
        if (rct.pos.x >= viewbuf.dim.x || rct.pos.y >= viewbuf.dim.y) {
                return ERRF;
        }

        for (int y = rct.pos.y; y < rct.pos.y + rct.sz.y; ++y) {
                for (int x = rct.pos.x; x < rct.pos.x + rct.sz.x; ++x) {
                        viewbuf.pxs[y * viewbuf.dim.x + x].c = 65;
                }
        }

        return FINE;
}

void flush_vb( ) {
        system("clear");
        for (int y = 0; y < viewbuf.dim.y; ++y) {
                for (int x = 0; x < viewbuf.dim.x; ++x) {
                        printf("%c", viewbuf.pxs[y * viewbuf.dim.x + x].c);
                }
                printf("\n");
        }
}

