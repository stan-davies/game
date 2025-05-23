#ifndef REND_H
#define REND_H

#include "shp/shp.h"

struct colour {
        uint            r       ;
        uint            g       ;
        uint            b       ;
};

struct pixel {
        char            c       ;
        struct  colour  col     ;
};

struct text {
        struct pixel   *img     ;
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

#endif
