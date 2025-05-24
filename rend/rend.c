#include "rend.h"

#include <stdio.h>
#include <stdlib.h>

#include "util.h"

#define PIPE_CHAR       124
#define PLUS_CHAR       43

static struct {
        struct pixel   *pxs     ;
        struct uvec     dim     ;
} viewbuf;

void init_vb(
        struct uvec     _dim
) {
        viewbuf.dim     = _dim;
        int     sz      = viewbuf.dim.x * viewbuf.dim.y;
        viewbuf.pxs     = malloc(sz * sizeof(struct pixel));
        for (int i = 0; i < sz; ++i) {
                viewbuf.pxs[i].c = 32;
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

        struct pixel *write = &(viewbuf.pxs[t.bb.pos.y * viewbuf.dim.x + t.bb.pos.x]);
        struct pixel *read  = t.img;
        char    c;
        struct uvec   curr = { 0, 0 };

        for (int i = 0; i < t.bb.dim.x * t.bb.dim.y; ++i) {
                c = read->c;
                read++;
                if (i % t.bb.dim.x == 0) {
                        write += viewbuf.dim.x - t.bb.dim.x;
                }

                curr.x = i % viewbuf.dim.x;
                curr.y = i / viewbuf.dim.y;
                if (vcont(curr)) {
                        write->c = c;
                }

                write++;
        }

        return FINE;
}
        
void flush_vb( ) {
        system("clear");

        char pad = PLUS_CHAR;

        for (int y = 0; y <= viewbuf.dim.y + 1; ++y) {
                if (0 == y || viewbuf.dim.y + 1 == y) {
                        pad = PLUS_CHAR;
                } else {
                        pad = PIPE_CHAR;
                }
                printf("%c", pad);
                for (int x = 0; x < viewbuf.dim.x; ++x) {
                        if (PLUS_CHAR == pad) {
                                printf("-");
                        } else {
                                printf("%c", viewbuf.pxs[(y - 1) * viewbuf.dim.x + x].c);
                        }
                }
                printf("%c\n", pad);
        }
}

int vcont(
        struct uvec     v
) {
        return v.x < viewbuf.dim.x && v.y < viewbuf.dim.y;
}


