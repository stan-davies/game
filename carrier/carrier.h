#ifndef CARRIER_H
#define CARRIER_H

#include "util/shp.h"

void init_carrier(
        void
);

void free_carrier(
        void
);

void spawn_laser(
        struct uvec     pos
);

void poll_carrier(
        void
);

#endif
