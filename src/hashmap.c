#ifdef ACL_LITTLE_ENDIAN
#define LEFT_OR_RIGHT_SHIFT >>
#else
#ifdef ACL_BIG_ENDIAN
#define LEFT_OR_RIGHT_SHIFT <<
#else
#error "endianiss not specified. make sure to properly add the cmake subdirectory."
#endif
#endif 
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <acl/hashmap.h>
#include <acl/array.h>
#include <stdint.h>
#include <string.h>

size_t acl_hash(void *data, size_t dataSize, size_t bucketBits) {
	switch(dataSize) {
		case 1:
			return (uint8_t)(101u * *(uint8_t*)data >> (8 - bucketBits));
		case 2: {
				uint16_t cache;
				memcpy(&cache, data, 2);
				return (uint16_t)(15227u * cache >> (16 - bucketBits));
			}
		case 3:
		case 4: {
				uint32_t cache = 0;
				memcpy(&cache, data, dataSize);
				return (uint32_t)(4000846301u * cache >> (32 - bucketBits));
			}
		default:
			if(dataSize <= 8) {
				 uint64_t cache = 0;
				 memcpy(&cache, data, dataSize);
				 return (uint64_t)(10223372036854775833u * cache >> (64 - bucketBits));
			 }
			uint8_t rest = (uintptr_t)data % sizeof(uint64_t);
			size_t data_len = dataSize / sizeof(uint64_t);
			uint8_t restEnd = dataSize % sizeof(uint64_t);
			if(restEnd) ++data_len;
			uint64_t *cache;
			if(rest) {
				cache = malloc(data_len * sizeof *cache);
				memcpy(cache, data, dataSize);
				cache[data_len - 1] = 0;
			}
			else cache = data;
			uint64_t hash = 0;
			for(size_t i = 0; i < data_len - 1; ++i) { 
				hash ^= (uint64_t)(10223372036854775833u * cache[i]);
			}
				hash ^= (uint64_t)(10223372036854775833u * cache[data_len - 1] & (18446744073709551615u LEFT_OR_RIGHT_SHIFT (sizeof *cache - restEnd)));
				free(cache);
				return hash >> (64 - bucketBits);
	}
}
union acl_hashmap_meta* acl_hashmap_create(size_t bucketCount, size_t sizeOneElement, size_t keySize) {
	union acl_hashmap_meta *hashmap_meta = malloc(sizeof *hashmap_meta + bucketCount * sizeof(void*));
	hashmap_meta->bucketCount = bucketCount;
	hashmap_meta->sizeOneElement = sizeOneElement;
	hashmap_meta->keyBits = log2(keySize);
	void **hashmap_buckets = (void**)(hashmap_meta + 1);
	for(size_t i; i < bucketCount; ++i) {
		hashmap_buckets[i] = acl_arraylist_create(0, sizeOneElement);
	}
	return hashmap_meta;
}

void acl_hashmap_put(union acl_hashmap_meta *hashmap_meta, void *key, void *element) {
	void **hashmap_buckets = (void**)(hashmap_meta + 1);

}
#include <stdio.h>
int main() {
	int baum[3] = {89, 120, 36};
	printf("Hash: %lu\n", acl_hash(baum, 3 * sizeof *baum , 5));
}
