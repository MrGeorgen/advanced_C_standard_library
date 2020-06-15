#include <stdio.h>
#include "array.h"
#include <stddef.h>

int main() {
	int *int_array = acl_arraylist_create(2, sizeof (int));
	int_array[0] = 28;
	int_array[1] = 20;
	for(int i = 0; i < 10; ++i) acl_arraylist_append(int_array, &i);
	for(int i = 0; i < 12; ++i) printf("Index: %d Value: %d\n", i, int_array[i]);
}
