#ifndef _acl_hashmap_h
#define _acl_hashmap_h
#include <stddef.h>
#include <stdbool.h>
#define acl_hashmap_create(type, keyType, bucketCount) acl_hashmap_init(bucketCount, sizeof(struct{keyType c; type d;}), offsetof(struct{keyType c; type d;}, d), sizeof(keyType))
union acl_hashmap_meta {
        void *dummy_ptr;
        struct {
        	size_t bucketBits;
        	size_t sizeOneElement;
		size_t keySize;
		size_t offset;
        };
};
union acl_hashmap_meta* acl_hashmap_init(size_t bucketCount, size_t sizeOneElement, size_t offset, size_t keySize);
void* acl_hashmap_declare(union acl_hashmap_meta *hashmap_meta, void *key);
void* acl_hashmap_get(union acl_hashmap_meta *hashmap_meta, void *key);
bool acl_hashmap_remove;
#endif
