#ifndef _acl_array_h
#define _acl_array_h
#include <stddef.h>
size_t acl_arraylist_len(void *arraylist);
void acl_arraylist_free(void *arraylist);
void* acl_arraylist_remove(void *arraylist_void, size_t index);
void* acl_arraylist_create(size_t array_size, size_t sizeof_one_element);
void* acl_arraylist_append(void *arraylist_void, void *element_void);
#endif
