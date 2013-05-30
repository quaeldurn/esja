#include <stdio.h>

int main() 
{
	unsigned int n = 0;
	unsigned long long int i;
	for (i; i < 12000000; i *= 4) {
		printf("%2d :: 0\t%llu\t%llu\t%llu\n", n, i, i*2, i*3);
		n++;
	}
}
