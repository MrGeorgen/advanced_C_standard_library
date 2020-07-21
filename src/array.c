#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

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
	arraylist_new->len = array_size;
	arraylist_new->cap = array_size;
	arraylist_new->sizeof_one_element = sizeof_one_element;
	return arraylist_new+1;
}

void* acl_arraylist_append(void *arraylist_void, void *element) {
	union arraylist_meta *arraylist = arraylist_void;
	--arraylist;
	if(arraylist->len == arraylist->cap) {
		arraylist->cap = arraylist->len + 10;
		arraylist = realloc(arraylist, arraylist->cap * arraylist->sizeof_one_element + sizeof *arraylist);
		if(!arraylist) return NULL;
	}
	memcpy((char*)(arraylist + 1) + arraylist->sizeof_one_element * arraylist->len, element, arraylist->sizeof_one_element);
	++arraylist->len;
	return arraylist+1;
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
