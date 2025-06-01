#ifndef UTIL_H
#define UTIL_H

#include "shp.h"
#include "input/input.h"
#include "player/player.h"
#include "rend/rend.h"
#include "rend/text.h"

#define ERRF    0
#define FINE    1

#define TRUE    1
#define FALSE   0

#ifndef NULL
#define NULL    ( (void *) 0 )
#endif

void prog_init( );

void prog_free( );

#endif
