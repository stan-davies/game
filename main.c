#include "rend/rend.h"
#include "rend/text.h"
#include "util.h"

#include <stdio.h>

int main() {
        struct uvec dim = { 80, 20 };
        init_vb(dim);

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

        struct uvec test_pos = { 5, 5 };
        struct uvec test_dim = { 2, 2 };
        struct text test = make_t(
                "^9AAAA^E",
                test_dim,
                test_pos
        );

        if (ERRF == blit_img(w)) {
                printf("Problem 0!\n");
                return 0;
        }

        if (ERRF == blit_img(t)) {
                printf("Problem!\n");
                return 0;
        }

        if (ERRF == blit_img(t2)) {
                printf("Problem 2!\n");
                return 0;
        }

        if (ERRF == blit_img(test)) {
                printf("Problem 3!\n");
                return 0;
        }

        flush_vb();

        free_vb();
        free_t(&t);
        free_t(&t2);
        free_t(&test);

        return 0;
}
