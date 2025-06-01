#include "util/util.h"

#include <stdio.h>

int main() {
        printf("Start strong!\n");


        prog_init();


        printf("Keep up...\n");

        // ---- create textures ----

        struct uvec w_pos = { 35, 15 };
        struct uvec w_dim = { 25, 1  };
        struct text w = make_t(
                "^4~~~~~~~~~~~~~~~~~~~~~~~~~~E",
                w_dim,
                w_pos
        );

        struct uvec i_pos = { 40, 10 };
        struct uvec i_dim = { 3 , 6  };
        struct text t = make_t(
                "^2 ,  0 ^7-^2@ .@;^? | ^7 | ^E",
                i_dim,
                i_pos
        );

        struct uvec t2_pos = { 50, 9  };
        struct uvec t2_dim = { 5 , 5  };
        struct text t2 = make_t(
                "^2 a .,0,^:@ *^2@ \"0^:\" \"^7Y  ^?  |  ^E",
                t2_dim,
                t2_pos
        );

        printf("Textures!\n");

        for (;;) {
                // ---- blit textures ---- 

                if (ERRF == blit_img(w)) {
                        printf("Problem 0!\n");
                        goto exit;
                }

                if (ERRF == blit_img(t)) {
                        printf("Problem!\n");
                        goto exit;
                }

                if (ERRF == blit_img(t2)) {
                        printf("Problem 2!\n");
                        goto exit;
                }

                printf("blit\n");

                draw_player();

                printf("player blit\n");

                // ---- stuff happens ----

                flush_vb();

                printf("flush\n");

                struct action inp = getact();
                if (inp.act == INVALID_ACTION || inp.mod == INVALID_ACTION) {
                        break;
                }

                printf("take input\n");

                do_cmd(inp);

                printf("processed\n");
        }

        printf("all done!\n");

exit:
        free_t(&w);
        free_t(&t);
        free_t(&t2);
        prog_free();
        return 0;
}
