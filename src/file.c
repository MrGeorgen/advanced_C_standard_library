#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
char* acl_ReadFileString(char *filePath, bool *sucess){
	FILE *fp = fopen(filePath, "rb");
	size_t lSize;
	char *buffer;
	if(!fp) {
		*sucess = false;
		return buffer;
	}
	fseek(fp, 0L, SEEK_END);
	lSize = ftell(fp);
	rewind(fp);
	buffer = malloc(lSize + 1);
	if(!buffer) {
		fclose(fp);
		*sucess = false;
		return buffer;
	}
	size_t readReturn = fread(buffer, lSize, 1, fp);
	fclose(fp);
	if(readReturn != 1) {
		*sucess = false;
	}
	*sucess = true;
	return buffer;
}
