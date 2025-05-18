#include "rend/rend.h"
#include "util.h"

int main() {
        struct rect r = {
                5, 5,
                5, 5
        };

        struct uvec dim = { 80, 20 };
        init_vb(dim);

        if (ERRF == blit(r)) {
                // =(
        }

        flush_vb();

        return 0;
}
