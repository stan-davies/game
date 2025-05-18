#include "rend.h"

#include <stdio.h>
#include <stdlib.h>

#include "util.h"

static struct {
        struct pixel   *pxs     ;
        uint            w       ;
        uint            h       ;
} viewbuf;

void init_vb(
        uint            w       ,
        uint            h
) {
        viewbuf.w       = w;
        viewbuf.h       = h;
        viewbuf.pxs     = calloc(w * h, sizeof(struct pixel));
        for (int i = 0; i < w * h; ++i) {
                viewbuf.pxs[i].c = 32;
        }
}

int blit(
        struct rect     rct
) {
        if (rct.pos.x >= viewbuf.w || rct.pos.y >= viewbuf.h) {
                return ERRF;
        }

        for (int y = rct.pos.y; y < rct.pos.y + rct.sz.y; ++y) {
                for (int x = rct.pos.x; x < rct.pos.x + rct.sz.x; ++x) {
                        viewbuf.pxs[y * viewbuf.w + x].c = 65;
                }
        }

        return FINE;
}

void flush_vb( ) {
        system("clear");
        for (int y = 0; y < viewbuf.h; ++y) {
                for (int x = 0; x < viewbuf.w; ++x) {
                        printf("%c", viewbuf.pxs[y * viewbuf.w + x].c);
                }
                printf("\n");
        }
}

