#if defined(__STDC__)
#if (__STDC_VERSION__ >= 201112L)
#include <stdalign.h>
#include <stddef.h>
#else
#define alignof(type) offsetof(struct { char c; type d; }, d)
typedef union {
	double dummy_double;
	long double dummy_long_double;
	long long dummy_long_long;
        void *dummy_ptr;
        void (*dummy_func_ptr)(void);
} max_align_t;
#endif
#endif
#include <stdio.h>
