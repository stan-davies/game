#include "util/util.h"

#include <stdio.h>

int main() {
        prog_init();

        for (;;) {
                if (ERRF == blit_world()) {
                        printf("Problem blitting world.\n");
                        goto exit;
                }

                poll_spawn();

                draw_player();

                flush_vb();

                if (!getact()) {
                        goto exit;
                }
        }

exit:
        prog_free();
        return 0;
}
