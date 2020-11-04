#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
char* acl_ReadTextFile(FILE *file, bool *sucess){
	size_t lSize;
	char *buffer;
	if(!file) {
		*sucess = false;
		return buffer;
	}
	fseek(file, 0L, SEEK_END);
	lSize = ftell(file);
	rewind(file);
	buffer = malloc(lSize + 1);
	if(!buffer) {
		*sucess = false;
		return buffer;
	}
	size_t readReturn = fread(buffer, lSize, 1, file);
	*sucess = readReturn == 1;
	buffer[lSize] = '\0';
	return buffer;
}
