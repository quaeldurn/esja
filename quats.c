#include <stdio.h>

int main() 
{
	int n = 0;
	long int i;
	for (i=1; i < 12000000; i *= 4) {
		printf("%2d :: 0\t%lu\t%lu\t%lu\n", n, i, i*2, i*3);
		n++;
	}
}
