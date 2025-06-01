#ifndef TEXT_H
#define TEXT_H

#include "util/shp.h"

struct pixel {
        char            c       ;
        int             col     ;
};

struct text {
        struct pixel   *img     ;
        struct rect     bb      ;
};

struct text make_t(
        char           *img     ,
        struct uvec     _dim    ,
        struct uvec     _pos
);

void free_t(
        struct text    *t
);

#endif
