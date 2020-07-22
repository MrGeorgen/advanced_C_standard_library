#include <math.h>
const unsigned acl_w = sizeof (unsigned) * 8;
const unsigned acl_m = 9;
unsigned hash(unsigned K) {
	return (149695736*K) >> (acl_w-acl_m);
}
