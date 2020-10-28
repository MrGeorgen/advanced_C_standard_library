/* The following macro alows the usage of the sizeof operator without an identifier */
#include <stddef.h>
#define acl_sizeof(type) offsetof(struct{type a; char b;}, b)
offsetof(struct{type a; char b;}, b)
