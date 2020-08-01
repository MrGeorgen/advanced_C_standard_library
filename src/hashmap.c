#include <math.h>
#include <acl/alignof.h>
#include <stddef.h>
#include <stdlib.h>
#include <acl/hashmap.h>
#include <acl/array.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#ifdef ACL_LITTLE_ENDIAN
#define LEFT_OR_RIGHT_SHIFT >>
#else
#ifdef ACL_BIG_ENDIAN
#define LEFT_OR_RIGHT_SHIFT <<
#else
#error "endianiss not specified. make sure to properly add the cmake subdirectory."
#endif
#endif 
#define acl_hashVarLen(type)\
	if(((uintptr_t)data & (alignof(type) - 1)) == 0) {\
		printf(#type);\
		type *src;\
		for(uint64_t *keySrc = data; (char*)(keySrc + 1) <= dest; ++keySrc) {\
			src = (type*)keySrc;\
			for(type *hashValue_ptr = (type*)&hashValue; src < (type*)(keySrc + 1); ++src, ++hashValue_ptr) {\
				*hashValue_ptr ^= *src;\
			}\
		}\
		char *hash_char = (char*)&hashValue;\
		for(char *i = (char*)src; i <= dest; ++i, ++hashValue) {\
			*hash_char ^= *i;\
		}\
	}

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
			uint64_t hashValue = 0;
			char * dest = (char*)data + dataSize - 1;
			acl_hashVarLen(uint64_t)
			else acl_hashVarLen(uint32_t)
			else acl_hashVarLen(uint16_t)
			else acl_hashVarLen(uint8_t)
			return hashValue * 10223372036854775833u >> (64 - bucketBits);
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
	char baum[10] = {1};
	char blau[10] = {1};
	char green[10] = {1};
	char w[10] = {1};
	printf("Hash: %lu\n", acl_hash(baum, 9 * sizeof *baum , 5));
	printf("Hash: %lu\n", acl_hash(blau, 9 * sizeof *baum , 5));
	printf("Hash: %lu\n", acl_hash(green, 9 * sizeof *baum , 5));
	printf("Hash: %lu\n", acl_hash(w, 9 * sizeof *baum , 5));
}
