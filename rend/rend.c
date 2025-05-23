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
        if (t.pos.x < 0 || t.pos.x >= viewbuf.dim.x
                || t.pos.y < 0 || t.pos.y >= viewbuf.dim.y) {
                return ERRF;
        }

        struct pixel *write = &(viewbuf.pxs[t.pos.y * viewbuf.dim.x + t.pos.x]);
        struct pixel *read  = t.img;
        char    c;

        for (int i = 0; i < t.dim.x * t.dim.y; ++i) {
                c = read->c;
                read++;
                if (i % t.dim.x == 0) {
                        write += viewbuf.dim.x - t.dim.x;
                }

                write->c = c;
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

void free_vb( ) {
        free(viewbuf.pxs);
        viewbuf.pxs = NULL;
}

struct text make_t(
        char           *img     ,
        struct uvec     _dim    ,
        struct uvec     _pos
) {
        struct text t = {
                .img = calloc(_dim.x * _dim.y, sizeof(struct pixel)),
                .dim = _dim,
                .pos = _pos,
        };

        struct pixel c;
        for (int i = 0; i < t.dim.x * t.dim.y; ++i) {
                c.c = img[i];
                t.img[i] = c;
        }

        return t;
}

void free_t(
        struct text    *t
) {
        free(t->img);
        t->img = NULL;
}
