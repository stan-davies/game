#include "util/util.h"

int main() {
        prog_init();

        for (;;) {
                poll_carrier();

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
