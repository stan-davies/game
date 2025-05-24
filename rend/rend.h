#ifndef REND_H
#define REND_H

#include "shp/shp.h"
#include "text.h"

#include <stddef.h>


// --- 

void init_vb(
        struct uvec     _dim
);

void free_vb( );

// --- 

int blit_img(
        struct text     t
);

void flush_vb( );

// --- 

int vcont(
        struct uvec     v
);

#endif
