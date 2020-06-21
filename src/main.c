#include <stdio.h>
#include "array.h"
#include <stddef.h>
#include "file.h"
#include <stdbool.h>
int main() {
	bool sucess;
	char *content = acl_ReadFileString("LICENSE", &sucess);
	if(sucess) {
		printf("%s", content);
	}
	else printf("Erorror\n");
}
