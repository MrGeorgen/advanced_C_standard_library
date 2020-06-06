#ifndef array_h
#define array_h
void* arraylist_create(size_t array_size, size_t sizeof_one_element);
void* arraylist_append(void *arraylist_void, void *element_void);
#endif
