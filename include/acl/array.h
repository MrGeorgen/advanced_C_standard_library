#ifndef _acl_array_h
#define _acl_array_h
#include <stddef.h>
union acl_arraylist_meta {
	double dummy_double;
	long double dummy_long_double;
	long long dummy_long_long;
        void *dummy_ptr;
        void (*dummy_func_ptr)(void);
        struct {
        	size_t len;
        	size_t cap;
		size_t sizeof_one_element;
        };
};
inline size_t acl_arraylist_len(void *arraylist) {
	return ((union acl_arraylist_meta*)arraylist - 1)->len;
}
void acl_arraylist_free(void *arraylist);
void* acl_arraylist_remove(void *arraylist_void, size_t index);
void* acl_arraylist_create(size_t array_size, size_t sizeof_one_element);
void* acl_arraylist_append(void *arraylist_void, void *element);
void* acl_arraylist_append_ptr(void *arraylist_void, void **append_element);
#endif
