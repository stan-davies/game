#ifndef TEXT_H
#define TEXT_H

#include "util/shp.h"

struct pixel {
        char            c       ;
        int             col     ;

// Do not use or access, padding bytes.
        char            p1      ;
        char            p2      ;
        char            p3      ;
};

struct text {
        struct rect     bb      ;
        struct pixel   *img     ;
};

struct text make_t(
        char           *img     ,
        struct uvec     _dim    ,
        struct uvec     _pos
);

void reframe_t(
        struct text    *t,
        char           *nimg
);

void free_t(
        struct text    *t
);

#endif
