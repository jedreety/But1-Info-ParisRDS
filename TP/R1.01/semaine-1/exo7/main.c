#include <stdio.h>
#include <limits.h>

int main() {

	printf("Les limites des types de base en C :\n");

	printf("char : %d %d\n", CHAR_MIN, CHAR_MAX);
	printf("short : %d %d\n", SHRT_MIN, SHRT_MAX);
	printf("int : %d %d\n", INT_MIN, INT_MAX);
	printf("long : %ld %ld\n", LONG_MIN, LONG_MAX);
	printf("long long : %lld %lld\n", LLONG_MIN, LLONG_MAX);

	printf("unsigned char : %d\n", UCHAR_MAX);
	printf("unsigned short : %d\n", USHRT_MAX);
	printf("unsigned int : %u\n", UINT_MAX);
	printf("unsigned long : %lu\n", ULONG_MAX);
	printf("unsigned long long : %llu\n", ULLONG_MAX);

	return 0;
}
