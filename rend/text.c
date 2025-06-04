#include "text.h"

#include <stdlib.h>

#include "util/util.h"
#include "colour/colour.h"

#define CHAR_CIRCUM     94
#define CHAR_ZERO       48

struct text make_t(
        char           *img     ,
        struct uvec     _dim    ,
        struct uvec     _pos
) {
        struct text t = {
                .img = calloc(_dim.x * _dim.y, sizeof(struct pixel)),
                .bb  = { _pos, _dim }
        };

        struct pixel c = { .col = COL_WHITE };
        int r = 0;
        int col;
        int esc = FALSE;
        for (int i = 0;; ++i) {
                c.c = img[i];
                if (CHAR_CIRCUM == c.c) {
                        esc = 1 - esc;
                        continue;
                }
                if (esc) {
                        col = c.c - CHAR_ZERO;
                        if (col > COL_WHITE) {
                                break;
                        }
                        c.col = col;
                        esc = FALSE;
                        continue;
                }

                t.img[r++] = c;
        }

        return t;
}

void free_t(
        struct text    *t
) {
        free(t->img);
        t->img = NULL;
}
