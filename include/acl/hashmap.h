#ifndef _acl_hashmap_h
#define _acl_hashmap_h
#include <stddef.h>
union acl_hashmap_meta {
        void *dummy_ptr;
        struct {
        	size_t bucketCount;
        	size_t sizeOneElement;
		size_t keyBits;
        };
};
union acl_hashmap_meta* acl_hashmap_create(size_t bucketCount, size_t sizeOneElement, size_t keySize);
void acl_hashmap_put(union acl_hashmap_meta *hashmap_meta, void *key, void *element);
#endif
