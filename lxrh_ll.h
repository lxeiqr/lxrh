#pragma once

// If you use a custom allocator, please change LXRH_MALLOC, LXRH_FREE in your code

#ifndef LXRH_MALLOC
#define LXRH_MALLOC malloc
#endif

#ifndef LXRH_FREE
#define LXRH_FREE free 
#endif

#define LXRH_LL_DECLARE(NAME, TYPE) \
    typedef struct NAME { \
        struct NAME *next; \
        TYPE data; \
    } NAME ; \
    void NAME##_push(struct NAME **s, TYPE data); \
    struct NAME * NAME##_next(struct NAME *s); \
    struct NAME * NAME##_get(struct NAME *s, size_t index); \
    int NAME##_pop(struct NAME *s, size_t index); \
    void NAME##_free(struct NAME *s);

#define LXRH_LL_DEFINE(NAME, TYPE) \
    void NAME##_push(struct NAME **s, TYPE data) { \
        struct NAME **p = s; \
        while(*p != NULL) {p = &(*p)->next;} \
        *p = LXRH_MALLOC(sizeof(struct NAME )); \
        (*p)->data = data; \
        (*p)->next = NULL; \
    } \
    \
    struct NAME * NAME##_next(struct NAME *s) { \
        if(s == NULL) \
            return s; \
        else \
            return s->next; \
    } \
    struct NAME * NAME##_get(struct NAME *s, size_t index) { \
        struct NAME *next = s; \
        for(size_t i = 0; i < index; i++) { \
            if(next == NULL) return NULL; \
            next = NAME##_next(next); \
        } \
        \
        return next; \
    } \
    int NAME##_pop(struct NAME *s, size_t index) { \
        struct NAME *next, *p = s; \
        if(index == 0) \
            return -1; \
        \
        p = NAME##_get(p, index-1); \
        if(p->next == NULL) \
            return -1; \
        \
        next = p->next->next; \
        LXRH_FREE(p->next); \
        p->next = next; \
        \
        return 0; \
    } \
    void NAME##_free(struct NAME *s) { \
        struct NAME *next; \
        while(s != NULL) { \
            next = s->next; \
            free(s); \
            s = next; \
        } \
    }

#define LXRH_LL_INIT(NAME, TYPE) \
    LXRH_LL_DECLARE(NAME, TYPE) \
    LXRH_LL_DEFINE(NAME, TYPE)
