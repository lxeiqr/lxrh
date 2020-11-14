#include <stdio.h>

#include <stdlib.h>
#include "../lxrh_arr.h"

LXRH_ARR_INIT(arr_int, int);

int main() {
    arr_int arr;

    arr_int_init(&arr);
    arr_int_push(&arr, 1);
    arr_int_push(&arr, 2);
    arr_int_push(&arr, 3);

    if(arr.p[1] != 2)
        return -1;
    
    if(arr_int_pop(&arr, 1) == 1)
        return -1;
    
    if(arr.p[1] != 3)
        return -1;

    if(arr.n != 2)
        return -1;
    
    arr_int_free(&arr);
    return 0;
}
