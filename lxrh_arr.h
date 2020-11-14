#pragma once
#include <string.h>

// If you use a custom allocator, please change LXRH_REALLOC, LXRH_FREE in your code

#ifndef LXRH_FREE
#define LXRH_FREE free 
#endif

#ifndef LXRH_REALLOC
#define LXRH_REALLOC realloc
#endif

#define LXRH_ARR_DECLARE(NAME, TYPE) \
    typedef struct NAME { \
        TYPE *p; \
        size_t n; \
    } NAME ; \
    void NAME##_init(struct NAME *s); \
    void NAME##_push(struct NAME *s, TYPE data); \
    int NAME##_pop(struct NAME *s, size_t index); \
    void NAME##_free(struct NAME *s);

#define LXRH_ARR_DEFINE(NAME, TYPE) \
    void NAME##_init(struct NAME *s) { \
        s->p = NULL; \
        s->n = 0; \
    } \
    void NAME##_push(struct NAME *s, TYPE data) { \
        s->p = LXRH_REALLOC(s->p, (++s->n) * sizeof(TYPE)); \
        s->p[s->n - 1] = data; \
    } \
    int NAME##_pop(struct NAME *s, size_t index) { \
        if(index + 1 > s->n) \
            return 1; \
        memmove(s->p + index, s->p + index + 1, s->n - index); \
        s->p = LXRH_REALLOC(s->p, (--s->n) * sizeof(TYPE)); \
        return 0; \
    } \
    void NAME##_free(struct NAME *s) { \
        LXRH_FREE(s->p); \
        NAME##_init(s); \
    }

#define LXRH_ARR_INIT(NAME, TYPE) \
    LXRH_ARR_DECLARE(NAME, TYPE) \
    LXRH_ARR_DEFINE(NAME, TYPE)
