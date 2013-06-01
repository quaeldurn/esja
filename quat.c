#include <stdio.h>

int main() 
{
	int n = 1;
	long long unsigned int i;
	for (i=1; n < 20; i *= 4) {
		printf("%2d :: 0%12llu%12llu%12llu\n", n, i, i*2, i*3);
		n++;
	}
}
