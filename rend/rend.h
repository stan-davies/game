#ifndef REND_H
#define REND_H

#include "shp/shp.h"
#include <stddef.h>

struct pixel {
        char            c       ;
//      int             colour  ;
};

struct text {
        struct pixel   *img     ;
        struct uvec     dim     ;
        struct uvec     pos     ;
};

void init_vb(
        struct uvec     _dim
);

int blit(
        struct rect     rct
);

int blit_img(
        struct text     t
);

void flush_vb( );

int vcont(
        struct uvec     v
);

void free_vb( );

struct text make_t(
        char           *img     ,
        struct uvec     _dim    ,
        struct uvec     _pos
);

void free_t(
        struct text    *t
);

#endif
