#ifndef SHP_H
#define SHP_H

typedef unsigned int    uint    ;

struct uvec {
        uint            x       ;
        uint            y       ;
};

struct vec {
        int             x       ;
        int             y       ;
};

struct rect {
        struct uvec     pos     ;
        struct uvec     dim     ;
};

#endif
