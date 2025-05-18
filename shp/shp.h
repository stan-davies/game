#ifndef SHP_H
#define SHP_H

typedef unsigned int    uint    ;

struct cart {
        uint            x       ;
        uint            y       ;
};

struct rect {
        struct cart     pos     ;
        struct cart     sz      ;
};

#endif
