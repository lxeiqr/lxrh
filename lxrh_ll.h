#pragma once

// If you use a custom allocator, please change LXRH_MALLOC, LXRH_FREE in your code

#ifndef LXRH_MALLOC
#define LXRH_MALLOC malloc
#endif

#ifndef LXRH_FREE
#define LXRH_FREE free 
#endif

#define LXRH_LL_DECLARE(NAME, TYPE) \
    typedef struct lxrh_ll_##NAME { \
        struct lxrh_ll_##NAME *next; \
        TYPE data; \
    } lxrh_ll_##NAME ; \
    void lxrh_ll_##NAME##_push(struct lxrh_ll_##NAME **s, TYPE data); \
    struct lxrh_ll_##NAME *lxrh_ll_##NAME##_next(struct lxrh_ll_##NAME *s); \
    struct lxrh_ll_##NAME *lxrh_ll_##NAME##_get(struct lxrh_ll_##NAME *s, size_t index); \
    int lxrh_ll_##NAME##_pop(struct lxrh_ll_##NAME *s, size_t index); \
    void lxrh_ll_##NAME##_free(struct lxrh_ll_##NAME *s);

#define LXRH_LL_DEFINE(NAME, TYPE) \
    void lxrh_ll_##NAME##_push(struct lxrh_ll_##NAME **s, TYPE data) { \
        struct lxrh_ll_##NAME **p = s; \
        while(*p != NULL) {p = &(*p)->next;} \
        *p = LXRH_MALLOC(sizeof(struct lxrh_ll_##NAME )); \
        (*p)->data = data; \
        (*p)->next = NULL; \
    } \
    \
    struct lxrh_ll_##NAME *lxrh_ll_##NAME##_next(struct lxrh_ll_##NAME *s) { \
        if(s == NULL) \
            return s; \
        else \
            return s->next; \
    } \
    struct lxrh_ll_##NAME *lxrh_ll_##NAME##_get(struct lxrh_ll_##NAME *s, size_t index) { \
        struct lxrh_ll_##NAME *next = s; \
        for(size_t i = 0; i < index; i++) { \
            if(next == NULL) return NULL; \
            next = lxrh_ll_##NAME##_next(next); \
        } \
        \
        return next; \
    } \
    int lxrh_ll_##NAME##_pop(struct lxrh_ll_##NAME *s, size_t index) { \
        struct lxrh_ll_##NAME *next, *p = s; \
        if(index == 0) \
            return -1; \
        \
        p = lxrh_ll_##NAME##_get(p, index-1); \
        if(p->next == NULL) \
            return -1; \
        \
        next = p->next->next; \
        LXRH_FREE(p->next); \
        p->next = next; \
        \
        return 0; \
    } \
    void lxrh_ll_##NAME##_free(struct lxrh_ll_##NAME *s) { \
        struct lxrh_ll_##NAME *next; \
        while(s != NULL) { \
            next = s->next; \
            free(s); \
            s = next; \
        } \
    }

#define LXRH_LL_INIT(NAME, TYPE) \
    LXRH_LL_DECLARE(NAME, TYPE) \
    LXRH_LL_DEFINE(NAME, TYPE)
