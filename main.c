#include "rend/rend.h"
#include "util.h"

#include <stdio.h>

int main() {
        struct rect r = {
                { 5, 5 },
                { 5, 5 }
        };

        struct uvec dim = { 80, 20 };
        init_vb(dim);

        if (ERRF == blit(r)) {
                printf("Problem!\n");
                return 0;
                // =(
        }

        flush_vb();

        free_vb();

        return 0;
}
