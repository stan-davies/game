#ifndef TEXT_H
#define TEXT_H

#include "shp/shp.h"

struct pixel {
        char            c       ;
//      int             colour  ;
};

struct text {
        struct pixel   *img     ;
        struct rect     bb      ;
//        struct uvec     dim     ;
//        struct uvec     pos     ;
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
