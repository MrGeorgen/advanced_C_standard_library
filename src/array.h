#ifndef array_h
#define array_h
void* acl_arraylist_create(size_t array_size, size_t sizeof_one_element);
void* acl_arraylist_append(void *arraylist_void, void *element_void);
#endif
