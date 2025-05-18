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
        uint            w       ,
        uint            h
);

int blit(
        struct rect     rct
);

void flush_vb( );

#endif
