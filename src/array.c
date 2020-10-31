#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <acl/array.h>

size_t acl_arraylist_len(void *arraylist);
void acl_arraylist_free(void *arraylist);

static inline void* acl_arraylist_resize(union acl_arraylist_meta *arraylist, int64_t relativLen) {
	size_t cap = arraylist->cap + relativLen;
	arraylist = realloc(arraylist, cap * arraylist->sizeof_one_element + sizeof *arraylist);
	if(arraylist != NULL) {
		arraylist->cap = cap;
	}
	return arraylist;
}
void* acl_arraylist_create(size_t array_size, size_t sizeof_one_element) {
	union acl_arraylist_meta *arraylist_new = malloc(array_size * sizeof_one_element + sizeof*arraylist_new);
	if(arraylist_new == NULL) return NULL;
	arraylist_new->len = array_size;
	arraylist_new->cap = array_size;
	arraylist_new->sizeof_one_element = sizeof_one_element;
	return arraylist_new+1;
}

void* acl_arraylist_append(void *arraylist_void, void *element) {
	void *element_append;
	union acl_arraylist_meta *arraylist = acl_arraylist_append_ptr(arraylist_void, &element_append);
	if(arraylist == NULL) return NULL;
	--arraylist;
	memcpy(element_append, element, arraylist->sizeof_one_element);
	return arraylist + 1;
}
void* acl_arraylist_append_ptr(void *arraylist_void, void **append_element) {
	union acl_arraylist_meta *arraylist = arraylist_void;
	--arraylist;
	if(arraylist->len == arraylist->cap) {
		arraylist = acl_arraylist_resize(arraylist, 10);
		if(arraylist == NULL) return NULL;
	}
	*append_element = (char*)(arraylist + 1) + arraylist->sizeof_one_element * arraylist->len;
	++arraylist->len;
	return arraylist + 1;
}

void* acl_arraylist_remove(void *arraylist_void, size_t index) {
	union acl_arraylist_meta *arraylist = (union acl_arraylist_meta*)arraylist_void - 1;
	char *arraylist_char = arraylist_void;
	if(index != arraylist->len - 1) {
		memcpy(arraylist_char + arraylist->sizeof_one_element * index, arraylist_char + arraylist->sizeof_one_element * (arraylist->len - 1), arraylist->sizeof_one_element);
	}
	--arraylist->len;
	if(arraylist->len < arraylist->cap - 20) {
		void* arraylistTmp = acl_arraylist_resize(arraylist, -10);
		if(arraylistTmp != NULL) arraylist = arraylistTmp;
	}
	return arraylist + 1;
}
