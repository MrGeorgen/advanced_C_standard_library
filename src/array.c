#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <acl/array.h>

union arraylist_meta {
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

void* acl_arraylist_create(size_t array_size, size_t sizeof_one_element) {
	union arraylist_meta *arraylist_new = malloc(array_size * sizeof_one_element + sizeof*arraylist_new);
	if(arraylist_new == NULL) return NULL;
	arraylist_new->len = array_size;
	arraylist_new->cap = array_size;
	arraylist_new->sizeof_one_element = sizeof_one_element;
	return arraylist_new+1;
}

void* acl_arraylist_append(void *arraylist_void, void *element) {
	void *append_pointer;
	void **element_append = &append_pointer;
	union arraylist_meta *arraylist = acl_arraylist_append_ptr(arraylist_void, element_append);
	if(arraylist == NULL) return NULL;
	--arraylist;
	memcpy(*element_append, element, arraylist->sizeof_one_element);
	return arraylist + 1;
}
void* acl_arraylist_append_ptr(void *arraylist_void, void **append_element) {
	union arraylist_meta *arraylist = arraylist_void;
	--arraylist;
	if(arraylist->len == arraylist->cap) {
		if(arraylist->len > 10) arraylist->cap = arraylist->len + 10;
		else arraylist->cap = arraylist->len * 2 + 1;
		arraylist = realloc(arraylist, arraylist->cap * arraylist->sizeof_one_element + sizeof *arraylist);
		if(!arraylist) return NULL;
	}
	*append_element = (char*)(arraylist + 1) + arraylist->sizeof_one_element * arraylist->len;
	++arraylist->len;
	return arraylist + 1;
}

void acl_arraylist_free(void *arraylist) {
	free((union arraylist_meta*)arraylist-1);
}

void* acl_arraylist_remove(void *arraylist_void, size_t index) {
	union arraylist_meta *arraylist = (union arraylist_meta*)arraylist_void - 1;
	char *arraylist_char = arraylist_void;
	if(index != arraylist->len - 1) {
		memcpy(arraylist_char + arraylist->sizeof_one_element * index, arraylist_char + arraylist->sizeof_one_element * (arraylist->len - 1), arraylist->sizeof_one_element);
	}
	--arraylist->len;
	if(arraylist->len < arraylist->cap - 10) {
		arraylist->cap = arraylist->len;
		arraylist = realloc(arraylist, arraylist->cap * arraylist->sizeof_one_element + sizeof *arraylist);
	}
	return arraylist;
}

size_t acl_arraylist_len(void *arraylist) {
	return ((union arraylist_meta*)arraylist - 1)->len;
}
