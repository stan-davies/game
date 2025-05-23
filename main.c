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

        printf("Okay...\n");

        struct uvec i_pos = { 40, 10 };
        struct uvec i_dim = { 3 , 6  };
        struct text t = make_t(
                " ,  0 -@ .@; |  | ",
                i_dim,
                i_pos
        );

        struct uvec t2_pos = { 50, 10 };
        struct uvec t2_dim = { 5 , 5  };
        struct text t2 = make_t(
                " a .,0,@ *@ \"0\" \"Y    |  ",
                t2_dim,
                t2_pos
        );

        if (ERRF == blit_img(t) || ERRF == blit_img(t2)) {
                printf("Problem!\n");
                return 0;
        }

        flush_vb();

        free_vb();
        free_t(&t);

        return 0;
}
