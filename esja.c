#include <stdio.h>
#include <stdlib.h>

#define MEM_SIZE 1728 // always a multiplict of 12

// this program is licensed under the GNU GPLv3

// make way to write and read *mem.
// way to translate bin or dem to quat
// way to directly change bit pairs to a qit value

int read_bit();
int read_qit();

typedef unsigned char word; // default word size = 8 bits
word r[35];	// defining registers
char cmnd[12], status = 'a';

int main() // the controle unit
{ 	
	void *mem = malloc(sizeof(word) * MEM_SIZE);	// mem allocation
	// MEM_SIZE*4 = total amount of qits
	int quit_loop;
	while (quit_loop) {
		terminal();
	}
}

int read_bit (word *c, int n)
{
	static unsigned char mask[] = {128, 64, 32, 16, 8, 4, 2, 1};
	return ((*c & mask[n]) != 0);
}

int read_qit (word *c, int n) // reads qit n in byte c
{
	int i;
	static word mask[] = {128, 64, 32, 16, 8, 4, 2, 1};
	if (n > 3) {
		printf("read_qit invalid index (n)"); 
		return 0;
	}
	if ((*c & mask[n*2]) == 0 && (*c & mask[n*2+1]) == 0) {
		return (0);
	} else if ((*c & mask[n*2+1]) == 0 && (*c & mask[n*2]) == 1) {
		return (1);	
	} else if ((*c & mask[n*2]) == 1 && (*c & mask[n*2+1]) == 0) {
		return (2);
	} else if ((*c & mask[n*2]) == 1 && (*c & mask[n*2+1]) == 1) {
		return (3);
	}
}

int mov(int n, word r2) 
{
	r[n] = r2;
}

int add(int n, word r2)
{
	r[n] = r[n] + r2;
}

int terminal()
{
	if (status == 'a') {
		printf("number of available qits: %d\n", MEM_SIZE*4);
		printf("Umriturnarrettur: Oll rettindi fraskilin\n");
		status = '0';
	}
	printf(">");
	fgets(cmnd, sizeof(cmnd), stdin);
}
int access_fs(void *pntr) 
{
;	
}

int write_fs(void *pntr, int raw) // writes info to *(pntr+1)[x]
{
;	
}
