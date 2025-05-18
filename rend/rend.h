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

void init_vb(
        struct uvec     _dim
);

int blit(
        struct rect     rct
);

void flush_vb( );

int vcont(
        struct uvec     v
);

void free_vb( );

#endif
