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

int blit_img(
        struct text     t
) {
        // check position in the right place
        if (t.pos.x < 0 || t.pos.x >= viewbuf.pos.x
                || t.pos.y < 0 || t.pos.y >= viewbuf.pos.y) {
                return ERRF;
        }

        struct pixel *write = &(viewbuf.pxs[t.pos.y * viewbuf.dim.x + t.pos.x]);
        struct pixel *read  = t.img;
        char    c;

        for (;;) {
                c = read->c;
                switch (c) {
                case 0:                         // null terminator
                        goto exit;
                case 10:                        // linefeed
                        read++;
                        write += viewbuf.dim.x;
                        continue;
                default:
                        write->c = c;
                        break;
                }
        }

exit:
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

void free_vb( ) {
        free(viewbuf.pxs);
        viewbuf.pxs = NULL;
}
