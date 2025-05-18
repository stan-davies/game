#include "rend/rend.h"
#include "util.h"

int main() {
        struct rect r = {
                5, 5,
                5, 5
        };

        init_vb(80, 20);

        if (ERRF == blit(r)) {
                // =(
        }

        flush_vb();

        return 0;
}


