#pragma once

// If you use a custom allocator, please change LXRH_MALLOC in your code

#ifndef LXRH_MALLOC
#define LXRH_MALLOC malloc
#endif

#define LXRH_LL_DECLARE(NAME, TYPE) \
    typedef struct lxrh_ll_##NAME { \
        struct lxrh_ll_##NAME *next; \
        TYPE data; \
    } lxrh_ll_##NAME ; \
    void lxrh_ll_##NAME##_push(struct lxrh_ll_##NAME **s, TYPE data);

#define LXRH_LL_DEFINE(NAME, TYPE) \
    void lxrh_ll_##NAME##_push(struct lxrh_ll_##NAME **s, TYPE data) { \
        struct lxrh_ll_##NAME **p = s; \
        while(*p != NULL) {p = &(*p)->next;} \
        *p = LXRH_MALLOC(sizeof(struct lxrh_ll_##NAME )); \
        (*p)->data = data; \
        (*p)->next = NULL; \
    } 

#define LXRH_LL_INIT(NAME, TYPE) \
    LXRH_LL_DECLARE(NAME, TYPE) \
    LXRH_LL_DEFINE(NAME, TYPE)
