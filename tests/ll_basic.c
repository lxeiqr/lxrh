#include <stdio.h>

#include <stdlib.h>
#include "../lxrh_ll.h"

LXRH_LL_INIT(ll_int, int);

int main() {
    ll_int *s = NULL;

    for(int i = 0; i < 10; i++)
        if(ll_int_push(&s, i)->data != i)
            return 1;

    if(ll_int_get(s, 5)->data != 5)
        return 1;
    
    ll_int_pop(&s, 5);
    
    if(ll_int_get(s, 8)->data != 9)
        return 1;
    
    // Test poppping first element
    ll_int_pop(&s, 0);
    if(ll_int_get(s, 0)->data != 1) 
        return 1;
    
    ll_int_free(s);

    return 0;
}
