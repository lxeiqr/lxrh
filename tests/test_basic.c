#include <stdio.h>

#include <stdlib.h>
#include "../lxrh_ll.h"

LXRH_LL_INIT(int, int);

int main() {
    lxrh_ll_int *s = NULL;

    lxrh_ll_int_push(&s, 2);
}
