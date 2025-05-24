#include "text.h"

#include <stdlib.h>

struct text make_t(
        char           *img     ,
        struct uvec     _dim    ,
        struct uvec     _pos
) {
        struct text t = {
                .img = calloc(_dim.x * _dim.y, sizeof(struct pixel)),
                .bb  = { _pos, _dim }
        };

        struct pixel c;
        for (int i = 0; i < t.bb.dim.x * t.bb.dim.y; ++i) {
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
