#include <stdio.h>

int main() 
{
	long int i;
	for (i=1; i < 120000; i *= 4) {
		printf("0\t%d\t%d\t%d\n", i, i*2, i*3);
	}
}
